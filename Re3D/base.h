#pragma once

#include"def.h"
//#include"BFC/bfstream.h"
#include"opencv2/core/mat.hpp"
#include<memory>

namespace ff {
	class BMStream;

	class ArgSet;
}

class CVRModel;

_RE3D_BEG



class _RE3D_API ModelData
{
	class Impl;
	Impl *ptr;
public:
	ModelData();

	~ModelData();

	ModelData(const ModelData &) = delete;
	ModelData& operator=(const ModelData&) = delete;

	void load(const char *file, bool createIfNotExist = false);
	
	void save(const char *file=nullptr);

	const char* getFile();        

	ff::BMStream* queryStream(const char *name);

	ff::BMStream& getStream(const char *name, bool createIfNotExist = false);

	void deleteStream(const char *name);

	int  nStreams();

	int _listStreams(char *vstrs[], int nmax);

	void listStreams(std::vector<std::string> &streams)
	{
		int size = this->nStreams();
		std::unique_ptr<char*[]> vstrs(new char*[size]);
		size=this->_listStreams(vstrs.get(), size);
		streams.resize(size);
		for (int i = 0; i < size; ++i)
			streams[i] = vstrs[i];
	}

	/*template<typename _DataT>
	void read(const std::string &name, _DataT &data)
	{
		auto &stream = this->getStream(name, false);
		stream >> data;
	}
	template<typename _DataT>
	void write(const std::string &name, const _DataT &data)
	{
		auto &stream = this->getStream(name, true);
		stream << data;
	}*/
//public:
//	const MeshInfo& getMeshInfo();
//
//	void  setMeshInfo(const MeshInfo &meshInfo);
//
//	void  setMeshInfo(CVRModel &mesh);
};

_RE3D_API void exec(const char *cmd);

inline void exec(const std::string &cmd) {
	exec(cmd.c_str());
}

//class _RE3D_API ModelInfo
//{
//public:
//	int   id;
//	std::string  name;
//};


class _RE3D_API Object
{
public:
	virtual void release();

	virtual ~Object();
};

typedef void* (*CreateObjectFuncT)();

//object type that supports dynamic-creation
class _RE3D_API DCObject
	:public Object
{
public:
	//virtual void setParams(const char *params);

	virtual void exec(const char *cmd, const char *args, void *param1 = nullptr, void *param2 = nullptr);

	//virtual DCObject* clone() =0 ;

public:
	static int   registerType(CreateObjectFuncT createFunc, const char *group, const char *type, int flag);

	static DCObject* createObject(const char *group, const char *type);

	template<typename _T>
	static _T* createObjectT(const char *group, const char *type)
	{
		return (_T*)createObject(group, type);
	}
};

#define DEFINE_RE3D_TYPE(className) public:\
	virtual void release() {delete this;}\
	static const char* getTypeName() {return #className;}


#define DEFINE_RE3D_GROUP(className) \
public:\
static std::shared_ptr<className> create(const char *type = nullptr){\
	return std::shared_ptr<className>(\
		createObjectT<className>(#className, type),\
		[](DCObject *ptr) {ptr->release(); }\
	);}\
static const char* getGroupName() {return #className;}


#define REGISTER_RE3D_TYPE2(objClass, className, flag) static void* create##objClass(){return new objClass;} \
 static int _auto_register_re3dobjs_##objClass=re3d::DCObject::registerType(create##objClass, objClass::getGroupName(), className, flag);

#define REGISTER_RE3D_TYPE(objClass, flag) REGISTER_RE3D_TYPE2(objClass, #objClass, flag)

//===============================================================

class _RE3D_API ObjectSet
	:public Object
{
	class CImpl;
	CImpl  *iptr;
public:
	ObjectSet();

	~ObjectSet();

	ObjectSet(const ObjectSet&) = delete;
	ObjectSet& operator=(const ObjectSet&) = delete;

	Object*  getObject(const char *name);

	void     setObject(const char *name, Object *obj);

	template<typename _T>
	_T* getObject(const char *name) {
		return reinterpret_cast<_T*>(this->getObject(name));
	}

	template<typename _T>
	_T* getObject() {
		return reinterpret_cast<_T*>(this->getObject(_T::getTypeName()));
	}

	/*virtual void setVar(const char *var, const char *val) = 0;

	virtual const char* getVar(const char *var) = 0;*/

protected:
	//call by getObject to create new object
	virtual Object* _createObject(const char *name);
};


class Model;

class _RE3D_API ModelObject
	:public DCObject
{
public:
	DEFINE_RE3D_GROUP(ModelObject)
public:
	virtual void onCreate(Model &model) = 0;
};

class ModelSet;

class _RE3D_API Model
	:public ObjectSet
{
	class CImpl;
	CImpl  *iptr;
public:
	Model(ModelSet *modelSet);

	~Model();
protected:
	virtual Object* _createObject(const char *name);
public:
	void set(int id, const char *modelName, const char *_3dFile, const char *dataFile);

	int getID();

	const char* getName();

	CVRModel& get3D();

	const char* get3DFile();

	ModelData& getData(bool createIfNotExist = true);

	const char* getDataFile();

	void setArgs(const char *args, bool fromFile = false);
	ff::ArgSet& getArgSet();
};

class _RE3D_API ModelSetObject
	:public DCObject
{
public:
	DEFINE_RE3D_GROUP(ModelSetObject)
public:
	virtual void onCreate(ModelSet &modelSet) = 0;
};


class _RE3D_API ModelSet
	:public ObjectSet
{
	class CImpl;
	CImpl *iptr;
protected:
	//call by getObject to create new object
	virtual Object* _createObject(const char *name);
public:
	ModelSet();

	~ModelSet();

	ModelSet(const ModelSet&) =delete;
	ModelSet& operator=(const ModelSet&) = delete;

	void load(const char *config);

	void setArgs(const char *args, bool fromFile=false);
	ff::ArgSet& getArgSet();

	//return nullptr if not found
	Model* getModel(int id);
	Model* getModel(const char *name);
	
	//throw exception if not found
	Model& operator[](int id);
	Model& operator[](const char *name);

	const std::vector<Model*>& getAll();
};

//=========================================================

class _RE3D_API MeshInfo
	:public ModelObject
{
	DEFINE_RE3D_TYPE(MeshInfo)
public:
	cv::Vec3f  center;

	cv::Vec3f  bbMin, bbMax;
public:
	virtual void onCreate(Model &model);

	cv::Matx44f getUnitize() const;
};


class _RE3D_API ObjectInfo2D
{
public:
	int		modelID;
	//Confidence of tracking result
	float confidence;

	cv::Rect  roi;
};

class _RE3D_API ObjectInfo3D
	:public ObjectInfo2D
{
public:
	//The rotation vector
	cv::Vec3f  rvec;
	//The translation vector
	cv::Vec3f  tvec;

	int			nContourPoints;
	const cv::Point  *contourPoints;
};

class _RE3D_API FrameObject
	:public DCObject
{
public:
	DEFINE_RE3D_GROUP(FrameObject)
};

class _RE3D_API FrameData
	:public ObjectSet
{
protected:
	virtual Object* _createObject(const char *name);
public:
	int          frameID = -1;
	cv::Matx33f  cameraK;

	ObjectInfo2D  *objs2D = nullptr;
	int            objs2DNumbers = 0;

	ObjectInfo3D  *objs3D = nullptr;
	int            objs3DNumbers = 0;
};


class _RE3D_API FrameProcessor
	:public DCObject
{
public:
	virtual void setModels(ModelSet *models, const char *params = nullptr) = 0;

	virtual int pro(const cv::Mat &img, FrameData &fd, const char *params = nullptr) = 0;
};

class _RE3D_API Detector3D
	:public FrameProcessor
{
	DEFINE_RE3D_GROUP(Detector3D)
};
typedef std::shared_ptr<Detector3D>  Detector3DPtr;

class _RE3D_API Tracker3D
	:public FrameProcessor
{
	DEFINE_RE3D_GROUP(Tracker3D)
public:
	virtual void setDetector(Detector3D *detector) = 0;
};
typedef std::shared_ptr<Tracker3D>  Tracker3DPtr;

_RE3D_END
