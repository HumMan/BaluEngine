
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <map>
#include <set>

#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include <World/IProperties.h>
#include <WorldObjects/Sprite/ISprite.h>
#include <WorldObjects/Sprite/IPhysShape.h>
#endif

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class TSkeleton;
	class IBaluClass;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum TKey :int
	{
		Left,
		Right,
		Up,
		Down
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	void TKey_register(TClassRegistryParams& params)
	{
		auto scl = RegisterEnum(params,
			"enum TKey\n"
			"{\n"
			"	Left,\n"
			"	Right,\n"
			"	Up,\n"
			"	Down,\n"
			"}\n");
	}
	static bool TKey_registered = TScriptClassesRegistry::RegisterEnum("TKey", TKey_register);
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

	enum TPhysBodyType
	{
		Static,
		Dynamic,
		Kinematic
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBone
	{
	public:
		virtual void SetTransform(TBaluTransform)=0;
	};

	
	class TBone : public IBone
	{
	private:
		TBone* parent;
		std::vector<TBone*> children;

		TBaluTransform local;
	public:
		TBone()
		{
		}
		TBone(TBone* parent);

		void SetTransform(TBaluTransform);
		TBaluTransform GetTransform();

		void AddChild(TBone* bone);
		int GetChildrenCount();
		TBone* GetChild(int index);

		void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
	};

#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkin
	{
	public:
		virtual void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global)=0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TSkin : public ISkin
	{
	private:
		std::vector<std::vector<TBaluClassSpriteInstance>> sprites_of_bones;
	public:
		TSkin()
		{
		}
		TSkin(int bones_count);
		void SetBoneSprite(int bone_index, TBaluSprite* sprite, TBaluTransform global);
		void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global);
		int GetBonesCount();
		std::vector<TBaluClassSpriteInstance>& GetSpritesOfBone(int bone_index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeleton
	{
	public:
		virtual ISkin* CreateSkin() = 0;
		virtual void DestroySkin(ISkin* skin) = 0;
		virtual int GetSkinsCount() = 0;
		virtual ISkin* GetSkin(int index) = 0;
		virtual IBone* CreateBone(IBone* parent) = 0;
		virtual void DestroyBone(IBone* bone) = 0;
		virtual int GetBoneIndex(IBone* bone) = 0;
		virtual IBone* GetRoot() = 0;
		//virtual std::vector<IBone*> GetAllBones() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TSkeleton : public ISkeleton
	{
	private:
		int root;
		std::vector<std::unique_ptr<TBone>> bones;
		std::vector<std::unique_ptr<TSkin>> skins;
	public:
		TSkeleton()
		{
			root = -1;
		}
		//TSkeleton(TSkeleton&& right);
		TSkin* CreateSkin();
		void DestroySkin(TSkin* skin);
		void DestroySkin(ISkin* skin);
		int GetSkinsCount();
		TSkin* GetSkin(int index);
		TBone* CreateBone(TBone* parent);
		IBone* CreateBone(IBone* parent);
		void DestroyBone(TBone* bone);
		void DestroyBone(IBone* bone);
		int GetBoneIndex(TBone* bone);
		int GetBoneIndex(IBone* bone);
		TBone* GetBone(int index)
		{
			return bones[index].get();
		}
		TBone* GetRoot();
		std::vector<TBone*> GetAllBones();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITrackFrame
	{
	public:
	};

	class TInterpolateCurve
	{
		enum Type
		{
			Linear,
			Stepped,
			Curve
		};
		//std::vector<TCurveSegment> segments;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TTrackFrame : public ITrackFrame
	{
	public:
		//int index;
		float time;
		float rotation;
		TTrackFrame()
		{
			time = 0;
			rotation = 0;
		}
		TTrackFrame(float time)
		{
			this->time = time;
			this->rotation = 0;
		}
		void Save(pugi::xml_node& parent_node, const int version) const;
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

	class TFrameComparer
	{
	public:
		bool operator() (const TTrackFrame& lhs, const TTrackFrame& rhs) const
		{
			//return lhs.index < rhs.index;
			return lhs.time < rhs.time;
		}
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITrack
	{
	public:
		virtual ITrackFrame* CreateFrame(float time, float rotation)=0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TTrack : public ITrack
	{
	private:
		TBone* bone;
		std::set<TTrackFrame, TFrameComparer> frames;
	public:
		TTrack()
		{
			bone = nullptr;
		}
		TTrack(TBone* bone);
		TTrackFrame* CreateFrame(float time, float rotation);
		void DestroyFrame(TTrackFrame* frame);
		TBone* GetBone();
		std::set<TTrackFrame, TFrameComparer>& GetFrames();
		void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITimeLine
	{
	public:
		virtual ITrack* CreateTrack(IBone* bone)=0;
		virtual void DestroyTrack(ITrack* track) = 0;
		virtual void SetTimelineSize(float size) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TTimeLine : public ITimeLine
	{
	private:
		std::vector<std::unique_ptr<TTrack>> tracks;
		std::string name;
		float timeline_size;
	public:
		TTimeLine()
		{
		}
		TTimeLine(std::string name);
		TTrack* CreateTrack(TBone* bone);
		ITrack* CreateTrack(IBone* bone);
		void DestroyTrack(TTrack* track);
		void DestroyTrack(ITrack* track);
		void SetTimelineSize(float size);
		float GetTimelineSize();
		std::string GetName();
		int GetTracksCount();
		TTrack* GetTrack(int index);
		void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeletonAnimation
	{
	public:
		virtual ITimeLine* CreateAnimation(std::string name)=0;
	};
#ifndef BALU_ENGINE_DLL_INTERFACES
	class TSkeletonAnimation : public ISkeletonAnimation
	{
	private:
		std::vector<std::unique_ptr<TTimeLine>> animations;
		TSkeleton* skeleton;
	public:
		TSkeletonAnimation();
		TSkeletonAnimation(TSkeleton* skeleton);
		TTimeLine* CreateAnimation(std::string name);
		void DestroyAnimation(TTimeLine* animation);
		int GetAnimationsCount();
		TTimeLine* GetAnimation(int index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassPhysBody
	{
	public:
		virtual void SetFixedRotation(bool fixed) = 0;
		virtual void SetPhysBodyType(TPhysBodyType type) = 0;
		virtual void Enable(bool enable) = 0;
		virtual bool IsEnable() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluClassPhysBody : public IBaluClassPhysBody
	{
	private:
		b2BodyDef body_def;
		bool enable;
	public:
		TBaluClassPhysBody();
		int GetSensorsCount();
		void SetFixedRotation(bool fixed);
		void SetPhysBodyType(TPhysBodyType type);
		void Enable(bool enable);
		bool IsEnable();
		b2BodyDef GetBodyDef();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	
	struct TSpriteWithClassCollide
	{
		IBaluSprite* sprite;
		IBaluClass* with_class;
		TScript script;
		TSpriteWithClassCollide()
		{
			sprite = nullptr;
			with_class = nullptr;
		}
		TSpriteWithClassCollide(IBaluSprite* sprite, IBaluClass* with_class, TScript script)
		{
			this->sprite = sprite;
			this->with_class = with_class;
			this->script = script;
		}
	};

	class IBaluClass: public virtual IBaluWorldObject
	{
	public:
		static std::string GetDefaultName()
		{
			return "class";
		}
		virtual TAABB2 GetAABB()=0;
		virtual IBaluClassSpriteInstance* AddSprite(IBaluSprite* sprite) = 0;

		virtual int GetSpritesCount() = 0;
		virtual IBaluClassSpriteInstance* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
		virtual IBaluClassPhysBody* GetPhysBody()=0;
		virtual ISkeleton* GetSkeleton()=0;

		virtual void OnKeyDown(TKey key, TScript callback) = 0;
		virtual void OnKeyUp(TKey key, TScript callback) = 0;
		virtual void OnBeforePhysicsStep(TScript callback) = 0;

		virtual std::map<TKey, std::vector<TScript>>& GetOnKeyDown() = 0;
		virtual std::map<TKey, std::vector<TScript>>& GetOnKeyUp() = 0;
		virtual std::vector<TScript>& GetOnBeforePhysicsStep() = 0;

		virtual void AddOnCollide(IBaluSprite* sprite, IBaluClass* obstancle_class, TScript script) = 0;
		virtual std::vector<TSpriteWithClassCollide>& GetOnCollide() = 0;
		virtual void RemoveOnCollide(int index) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluClass : public IBaluClass, public TBaluWorldObject
	{
	private:
		std::string class_name;

		int layer_id;

		std::vector<std::unique_ptr<TBaluClassSpriteInstance>> sprites;
		TBaluClassPhysBody phys_body;
		std::unique_ptr<TSkeleton> skeleton;
		std::unique_ptr<TSkeletonAnimation> skeleton_animation;
		TProperties properties;

		std::map<TKey, std::vector<TScript>> on_key_down_callbacks;
		std::map<TKey, std::vector<TScript>> on_key_up_callbacks;
		std::vector<TScript> before_physics_callbacks;

		std::vector<TSpriteWithClassCollide> on_collide_callbacks;

		void Initialize();

		TBaluWorld* world;
	public:

		void AddOnCollide(IBaluSprite* sprite, IBaluClass* obstancle_class, TScript callback);
		std::vector<TSpriteWithClassCollide>& GetOnCollide();
		TScript* GetOnCollide(IBaluSprite* sprite, TBaluClass* obstancle_class);
		void RemoveOnCollide(int index);

		TBaluClass(std::string name, TBaluWorld* world);

		IProperties* GetProperties();
		bool PointCollide(TVec2 class_space_point);
		TAABB2 GetAABB();

		virtual ~TBaluClass();

		//void OnMouseMove(TMouseMoveCallback);

		TBaluClassSpriteInstance* AddSprite(TBaluSprite* sprite);
		IBaluClassSpriteInstance* AddSprite(IBaluSprite* sprite);
		void RemoveSprite(TBaluSprite* sprite);
		int GetSpritesCount();
		TBaluClassSpriteInstance* GetSprite(int index);

		TBaluClassPhysBody* GetPhysBody();

		TSkeletonAnimation* GetSkeletonAnimation();
		TSkeleton* GetSkeleton();

		void OnKeyDown(TKey key, TScript callback);
		void OnKeyUp(TKey key, TScript callback);
		void OnBeforePhysicsStep(TScript callback);

		std::map<TKey, std::vector<TScript>>& GetOnKeyDown();
		std::map<TKey, std::vector<TScript>>& GetOnKeyUp();
		std::vector<TScript>& GetOnBeforePhysicsStep();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluSceneInstance* editor_scene_instance);
	};
#endif
#endif
}