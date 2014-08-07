
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
	const int source_len = 10e6;
	char* source=new char[source_len];
	int c=0;

	c=sprintf_s(source,source_len,"\n class TGame \n{");

	char* script_base_classes=NULL;
	{
		TFileData file("../../BaluScript/Source/NativeTypes/base_types.bscript", "rb");
		char* base_source = new char[source_len];
		base_source = file.ReadAll();
		base_source[file.GetSize()] = '\0';
		script_base_classes = base_source;
	}

	c += sprintf_s(&source[c], source_len-c, "%s" ,script_base_classes);
	c += sprintf_s(&source[c], source_len - c, "%s" ,script_mouse);
	c += sprintf_s(&source[c], source_len - c, "%s", script_keyboard);//TODO это же можно одной коммандой сделать
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_time);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_screen);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_texture);
	c += sprintf_s(&source[c], source_len-c, "%s", script_material);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_shape);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_body);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_sprite);
	c += sprintf_s(&source[c], source_len-c, "%s" ,script_instance);
	std::map<std::string,TBaluClass>::iterator i;

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		c += sprintf_s(&source[c], source_len - c,
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
					c += sprintf_s(&source[c], source_len - c,
							"\n func %s\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_GLOBALMOUSEDOWN:
				case EVENT_GLOBALMOUSEUP:
					{
					c += sprintf_s(&source[c], source_len - c,
							"\n func %s(TMouseButton button)\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_GLOBALMOUSEWHEEL:
					{
					c += sprintf_s(&source[c], source_len - c,
							"\n func %s(float delta)\
							\n {\
							\n %s\
							\n }",event_name[k],cl->events_code[k].c_str());
					}
					break;
				case EVENT_KEYDOWN:
				case EVENT_KEYUP:
					{
					c += sprintf_s(&source[c], source_len - c,
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
		c += sprintf_s(&source[c], source_len-c, "%s" ,"\n }");
	}

	c += sprintf_s(&source[c], source_len-c, "%s" ,script_global_vars);

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		c += sprintf_s(&source[c], source_len - c,
			"\n TDynArray<T%s> static %s;"
			,cl->class_name.c_str(),cl->class_name.c_str());
	}
	c += sprintf_s(&source[c], source_len - c,
		"\n }");

	char buf1[1000];

	FILE *stream;
	fopen_s( &stream, "baluscript.bscript", "w" );
	fprintf( stream, "%s", source);
	fclose( stream );
	TTime time;

	TBaluMouse::LinkExternMethods(&syntax);
	TBaluKeyboard::LinkExternMethods(&syntax);
	TBaluTime::LinkExternMethods(&syntax);
	TBaluScreen::LinkExternMethods(&syntax);
	TBaluShape::LinkExternMethods(&syntax);
	TBaluBody::LinkExternMethods(&syntax);
	TBaluMaterial::LinkExternMethods(&syntax);
	TBaluSprite::LinkExternMethods(&syntax);
	TBaluInstance::LinkExternMethods(&syntax);

	try
	{
		syntax.Compile(source, time);
	}
	catch (std::string ex)
	{

	}

	InitializeStaticClassFields(syntax.static_fields, static_objects);
	InitializeStaticVariables(syntax.static_variables, static_objects);

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
					sprintf_s(buff, "func TGame.T%s.%s", cl->class_name.c_str(), event_name[k]);
					break;
				case EVENT_GLOBALMOUSEDOWN:
				case EVENT_GLOBALMOUSEUP:
					sprintf_s(buff, "func TGame.T%s.%s(TMouseButton button)", cl->class_name.c_str(), event_name[k]);
					break;
				case EVENT_GLOBALMOUSEWHEEL:
					sprintf_s(buff, "func TGame.T%s.%s(float delta)", cl->class_name.c_str(), event_name[k]);
					break;
				case EVENT_KEYDOWN:
				case EVENT_KEYUP:
					sprintf_s(buff, "func TGame.T%s.%s(TKey key)", cl->class_name.c_str(), event_name[k]);
					break;
				default:assert(false);
				}
				cl->events[k]=syntax.GetMethod(buff);
			}
	}
	
	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		char buff[1000];
		sprintf_s(buff, "TGame.%s", cl->class_name.c_str());
		cl->objects_array = (TDynArr*)static_objects[syntax.GetStaticField(buff)->GetOffset()].get();
	}

	//получаем необходимые для взаимодействия со скриптом адреса
	Time = (TBaluTime*)static_objects[syntax.GetStaticField("TGame.Time")->GetOffset()].get();
	Mouse = (TBaluMouse*)static_objects[syntax.GetStaticField("TGame.Mouse")->GetOffset()].get();
	Keyboard = (TBaluKeyboard*)static_objects[syntax.GetStaticField("TGame.Keyboard")->GetOffset()].get();
	Screen = (TBaluScreen*)static_objects[syntax.GetStaticField("TGame.Screen")->GetOffset()].get();


	//инициализируем мир box2d
	b2AABB aabb;
	aabb.lowerBound.Set(-1000,-1000);
	aabb.upperBound.Set(1000,10000);
	phys_world=new b2World(b2Vec2(0,-10));
	//

	Time->engine=this;
	Mouse->engine=this;
	Screen->engine=this;
	Screen->Size=TVec2(1,1);
	Screen->Pos=TVec2(0,0);

	//инициализируем instances
	for(int i=0;i<start_instances.size();i++)
	{
		TDynArr* obj_arr = start_instances[i].class_pointer->objects_array;
		obj_arr->EmplaceBack(static_objects);
		TBaluInstance* inst = (TBaluInstance*)(obj_arr->GetElement(obj_arr->GetSize()-1));
		*inst=start_instances[i];

		TBaluShape* shape=&inst->sprite.shape;
		b2PolygonShape shape_def;
		shape_def.SetAsBox(shape->box_size_x, shape->box_size_y);
		//if(instances[i].object->sprite->shape!=NULL)
		{
			b2BodyDef body_def;
			body_def.position.Set(inst->pos[0],inst->pos[1]);
			if (shape->density!=0)
				body_def.type = b2_dynamicBody;
			//body_def.fixedRotation=true;
			body_def.angle=inst->angle;
			shape->body=phys_world->CreateBody(&body_def);
			shape->body->CreateFixture(&shape_def, shape->density);
			//shape->UpdatePhysShape();
		}//else
		//	shape->type=TBaluShape::FT_NONE;

		//int m=inst->class_pointer->events[EVENT_CREATE];
		//if(m!=-1)
		//{
		//	vmachine.Push((int)inst);
		//	vmachine.Execute(m,NULL,(int*)inst);
		//}
	}

	render.Set.VSync(true);
}
void TBaluEngine::Step(float step,double time)
{
	//scripts globals
	Time->Step=step;
	Time->Current=time;
	//scripts

	float room_size = 40;

	TMatrix<float, 4> ortho_m = TMatrix<float, 4>::GetOrtho(TVec2(0, 20), TVec2(1, 1)*room_size*1.1, -10, 10);
	TMatrix<float, 4> ortho_m_inv = ortho_m.GetInverted();
	render.Set.Projection(ortho_m);

	std::map<std::string,TBaluClass>::iterator i;
	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		for(int k=0;k<cl->objects_array->v->size();k++)
			if(cl->events[EVENT_STEP]!=NULL)
			{
				TBaluInstance* inst=(TBaluInstance*)(&(*cl->objects_array->v)[k]);
				std::vector<TStackValue> without_params;
				TStackValue result;
				TStackValue obj(true,cl->objects_array->el_class);
				obj.SetAsReference(inst);
				//cl->events[EVENT_STEP]->Run(static_objects, without_params, result, obj);
			}
	}
	//physics

	for(i=classes.begin();i!=classes.end();i++)
	{
		TBaluClass* cl=&i->second;
		for (int k = 0; k<cl->objects_array->GetSize(); k++)
		{
			TBaluInstance* inst = (TBaluInstance*)(cl->objects_array->GetElement(k));
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
			for (int k = 0; k<cl->objects_array->GetSize(); k++)
			{
				TBaluInstance* inst = (TBaluInstance*)(cl->objects_array->GetElement(k));
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

				TStreamsDesc desc;
				desc.AddStream(TStream::Vertex, TDataType::Float, 3, &fscr);
				desc.AddStream(TStream::Normal, TDataType::Float, 3, &fscr_normals);
				desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &fscr_coords);
				render.Draw(desc, TPrimitive::Quads, 4);
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
	//if(step<0.015f)
	for (int i = 0; i < 5;i++)
		phys_world->Step(0.005,1,1);
	//else
	{
		//phys_world->Step(0.0035f,30,10);
		/*int iter_count=int(step/0.015f)+1;
		for(int i=0;i<iter_count;i++)
			phys_world->Step(step/iter_count,10);*/
	}
}