
#include <baluEngine.h>

void TBaluScreen::SetPos(TVec2& use_pos)
{
	Pos=use_pos;
	//TODO сделать в baluengine
	engine->Mouse->WorldPos=engine->ScreenToWorld(engine->Mouse->Pos);
}


void TBaluScreen::SetSize(TVec2& use_size)
{
	Size=use_size;
	//TODO сделать в baluengine
	engine->Mouse->WorldPos=engine->ScreenToWorld(engine->Mouse->Pos);
}

void TBaluEngine::Start()
{
	//create and compile script
	char* source=new char[10e6];
	int c=0;

	c=sprintf(source,"\n class TGame \n{");
	strcpy(&source[c],script_base_classes);
	c+=strlen(script_base_classes);
	//c+=sprintf(&source[c],script_base_classes);//TODO нужно просто копировать а то проблемы с форматированием(проценты и т.д. упр. символы)
	c+=sprintf(&source[c],script_mouse);
	c+=sprintf(&source[c],script_keyboard);//TODO это же можно одной коммандой сделать
	c+=sprintf(&source[c],script_time);
	c+=sprintf(&source[c],script_screen);
	c+=sprintf(&source[c],script_texture);
	c+=sprintf(&source[c],script_material);
	c+=sprintf(&source[c],script_shape);
	c+=sprintf(&source[c],script_body);
	c+=sprintf(&source[c],script_sprite);
	c+=sprintf(&source[c],script_instance);
	std::map<std::string,TBaluClass>::iterator i;

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		c+=sprintf(&source[c],
			"\n class T%s:TInstance\
			\n {\
			\n\t %s"
			,cl->class_name.c_str(),cl->class_members.c_str());
		for(int k=0;k<MAX_EVENTS;k++){
			if(!cl->events_code[k].empty())
			{
				switch(k)
				{
				case EVENT_CREATE:
				case EVENT_DESTROY:
				case EVENT_STEP:
				case EVENT_GLOBALMOUSEMOVE:
					{
						c+=sprintf(&source[c],
							"\n func %s\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_GLOBALMOUSEDOWN:
				case EVENT_GLOBALMOUSEUP:
					{
						c+=sprintf(&source[c],
							"\n func %s(TMouseButton button)\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_GLOBALMOUSEWHEEL:
					{
						c+=sprintf(&source[c],
							"\n func %s(float delta)\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_KEYDOWN:
				case EVENT_KEYUP:
					{
						c+=sprintf(&source[c],
							"\n func %s(TKey key)\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				default:assert(false);
				}
			}
		}
		c+=sprintf(&source[c],"\n }");
	}

	c+=sprintf(&source[c],script_global_vars);

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		c+=sprintf(&source[c],
			"\n T%s[] static %s;"
			,cl->class_name.c_str(),cl->class_name.c_str());
	}
	c+=sprintf(&source[c],
		"\n }");

	char buf1[1000];

	FILE *stream;
	fopen_s( &stream, "baluscript.bscript", "w" );
	fprintf( stream, "%s", source);
	fclose( stream );
	TTime time;

	syntax.Compile(source,time);
	delete source;
	source=NULL;

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		char buff[1000];
		for(int k=0;k<MAX_EVENTS;k++)
			if(!cl->events_code[k].empty())
			{
				switch(k)
				{
				case EVENT_CREATE:
				case EVENT_DESTROY:
				case EVENT_STEP:
				case EVENT_GLOBALMOUSEMOVE:
					sprintf(buff,"func TGame.T%s.%s",cl->class_name.c_str(),event_name[k]);
					break;
				case EVENT_GLOBALMOUSEDOWN:
				case EVENT_GLOBALMOUSEUP:
					sprintf(buff,"func TGame.T%s.%s(TMouseButton button)",cl->class_name.c_str(),event_name[k]);
					break;
				case EVENT_GLOBALMOUSEWHEEL:
					sprintf(buff,"func TGame.T%s.%s(float delta)",cl->class_name.c_str(),event_name[k]);
					break;
				case EVENT_KEYDOWN:
				case EVENT_KEYUP:
					sprintf(buff,"func TGame.T%s.%s(TKey key)",cl->class_name.c_str(),event_name[k]);
					break;
				default:assert(false);
				}
				cl->events[k]=syntax.GetMethod(buff);
			}
	}

	//связываем внешние методы

	TVector<TExternMethod> extern_methods;

	TBaluMouse		::LinkExternMethods(extern_methods);
	TBaluKeyboard	::LinkExternMethods(extern_methods);
	TBaluTime		::LinkExternMethods(extern_methods);
	TBaluScreen		::LinkExternMethods(extern_methods);
	TBaluShape		::LinkExternMethods(extern_methods);
	TBaluBody		::LinkExternMethods(extern_methods);
	TBaluMaterial	::LinkExternMethods(extern_methods);
	TBaluSprite		::LinkExternMethods(extern_methods);
	TBaluInstance	::LinkExternMethods(extern_methods);

	for(int i=0;i<=extern_methods.GetHigh();i++)
		extern_methods[i].id=syntax.GetMethod(extern_methods[i].method_name);

	syntax.GetProgram(program,time);
	vmachine.SetProgram(&program);

	for(int i=0;i<=extern_methods.GetHigh();i++)
		program.SetExternalMethod(extern_methods[i].id,extern_methods[i].method_body);

	//

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		char buff[1000];
		sprintf(buff,"TGame.%s",cl->class_name.c_str());
		cl->objects_array=(TVirtualMachine::TDynArr*)&vmachine.Get(syntax.GetStaticField(buff)->GetOffset());
	}

	//получаем необходимые для взаимодействия со скриптом адреса
	Time=(TBaluTime*)&vmachine.Get(syntax.GetStaticField("TGame.Time")->GetOffset());
	Mouse=(TBaluMouse*)&vmachine.Get(syntax.GetStaticField("TGame.Mouse")->GetOffset());
	Keyboard=(TBaluKeyboard*)&vmachine.Get(syntax.GetStaticField("TGame.Keyboard")->GetOffset());
	Screen=(TBaluScreen*)&vmachine.Get(syntax.GetStaticField("TGame.Screen")->GetOffset());


	//инициализируем мир box2d
	b2AABB aabb;
	aabb.lowerBound.Set(-1000,-1000);
	aabb.upperBound.Set(1000,10000);
	phys_world=new b2World(aabb,b2Vec2(0,-10),true);
	//

	vmachine.ConstructStaticVars();

	Time->engine=this;
	Mouse->engine=this;
	Screen->engine=this;
	Screen->Size=TVec2(1,1);
	Screen->Pos=TVec2(0,0);

	//инициализируем instances
	for(int i=0;i<=start_instances.GetHigh();i++)
	{
		TBaluInstance* inst=(TBaluInstance*)(start_instances[i].class_pointer->objects_array->IncHigh(&vmachine));
		*inst=start_instances[i];

		TBaluShape* shape=&inst->sprite.shape;
		//if(instances[i].object->sprite->shape!=NULL)
		{
			b2BodyDef body_def;
			body_def.position.Set(inst->pos[0],inst->pos[1]);
			//body_def.fixedRotation=true;
			body_def.angle=inst->angle;
			shape->body=phys_world->CreateBody(&body_def);
			shape->UpdatePhysShape();
		}//else
		//	shape->type=TBaluShape::FT_NONE;

		int m=inst->class_pointer->events[EVENT_CREATE];
		if(m!=-1)
		{
			vmachine.Push((int)inst);
			vmachine.Execute(m,NULL,(int*)inst);
		}
	}
}
void TBaluEngine::Step(float step,double time)
{
	//scripts globals
	Time->Step=step;
	Time->Current=time;
	//scripts

	std::map<std::string,TBaluClass>::iterator i;
	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		for(int k=0;k<=cl->objects_array->GetHigh();k++)
			if(cl->events[EVENT_STEP]!=-1)
			{
				TBaluInstance* inst=(TBaluInstance*)cl->objects_array->Get(k);
				vmachine.Execute(cl->events[EVENT_STEP],(int*)inst);
			}
	}
	//physics

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		for(int k=0;k<=cl->objects_array->GetHigh();k++)
		{
			TBaluInstance* inst=(TBaluInstance*)cl->objects_array->Get(k);
			if(inst->sprite.shape.type==TBaluShape::FT_NONE)continue;
			b2Vec2 v=inst->sprite.shape.body->GetPosition();
			inst->pos[0]=v.x;
			inst->pos[1]=v.y;
			inst->angle=inst->sprite.shape.body->GetAngle();
		}
	}
	//draw
	render.BeginScene();
	{
		render.Set.ClearColor(0,0,0);
		render.Set.Color(1,1,1,1);
		render.Clear(true);

		render.Texture.Enable(true);

		render.AlphaTest.Enable(true);
		render.Blend.Enable(true);

		render.AlphaTest.Func(">=",0.1);
		render.Blend.Func("dc*(1-sa)+sc*sa");

		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//TVec<float,4> light_position(Mouse->WorldPos[0],Mouse->WorldPos[1],0.3,1);
		//GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
		//GLfloat mat_shininess[]={50.0};
		//GLfloat white_light[]={1.0,1.0,1.0,1.0};
		//GLfloat quad_att[]={0.01,0,0,0};


		//glClearColor(0.0,0.0,0.0,0.0);
		//glShadeModel(GL_SMOOTH);
		//glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		//glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
		//glLightfv(GL_LIGHT0,GL_POSITION, (GLfloat*)&light_position);
		//glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
		//glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
		//glLightfv(GL_LIGHT0,GL_LINEAR_ATTENUATION,quad_att);

		for(i=classes.begin();i!=classes.end();i++)
		{
			TBaluClass* cl=&i->second;
			for(int k=0;k<=cl->objects_array->GetHigh();k++)
			{
				TBaluInstance* inst=(TBaluInstance*)cl->objects_array->Get(k);
				render.Texture.Bind(inst->sprite.material.texture);
				//render.Set.Color(inst->material.color[0],inst->material.color[1],inst->material.color[2]);
				TQuad<float,3> fscr;
				TQuad<float,2> fscr_coords;
				TQuad<float,3> fscr_normals;
				fscr_normals[0]=TVec3(0,0,1);
				fscr_normals[1]=fscr_normals[0];
				fscr_normals[2]=fscr_normals[0];
				fscr_normals[3]=fscr_normals[0];
				fscr.Set(
					inst->pos+inst->sprite.local_pos,
					inst->sprite.size,
					inst->angle+inst->sprite.local_angle,
					inst->sprite.z_bias);
				fscr_coords.Set(TVec2(0.5,0.5),1,0);
				//render.Quads.Begin();
				//render.Quads.Draw(fscr,fscr_coords,fscr_normals);
				//render.Quads.End();
			}
		}

		render.Texture.Enable(false);
		render.AlphaTest.Enable(false);
		render.Blend.Enable(false);
	}
	render.EndScene();
	if(step<0.015f)
		phys_world->Step(step,10);
	else
	{
		phys_world->Step(0.015f,10);
		/*int iter_count=int(step/0.015f)+1;
		for(int i=0;i<iter_count;i++)
			phys_world->Step(step/iter_count,10);*/
	}
}