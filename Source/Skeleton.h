class TBone
{
	TBone* parent;
	std::list<TBone> children;
	
	TVec2 position;
	float rotation;
}

class TSkin
{
	class TBaluSpriteInstance
	{
	public:
		TBaluSprite* sprite;
		TBaluTransform local;
		TBaluSpriteInstance(TBaluSprite* sprite)
		{
			this->sprite = sprite;
		}
	};
	std::vector<TBaluClass::SpriteInstance> sprites;
}

class TSkeleton
{
	std::unique_ptr<TBone> root;
	std::vector<TBone*> bones;
}