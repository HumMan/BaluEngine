
class TBaluWorld
{
private:
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;
public:
	virtual ~TBaluWorldDef();

	TBaluMaterial* CreateMaterial(char* mat_name, char* tex_path, TVec4 use_color);
	TBaluSprite* CreateSprite(char* sprite_name, char* mat_name, TVec2 use_size, float use_local_angle, TVec2 use_local_pos, float use_z_bias);
	TBaluClass* CreateClass(char* class_name);
	TBaluScene* CreateScene(char* scene_name);

	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 WorldToScreen(const TVec2& v);

	void SetAcitveScene();
};