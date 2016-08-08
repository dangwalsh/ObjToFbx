#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include "ObjScene.h"
#include <string>
#include <fbxsdk.h>

class ObjScene;

class ObjMaterial
{
public:
    ObjMaterial(ObjScene* pScene, std::string& pString);
    virtual ~ObjMaterial();

    virtual void SetKa(double pValues[3]);
    virtual void SetKd(double pValues[3]);
    virtual void SetKs(double pValues[3]);
    virtual void SetD(double* pValue);
    virtual void SetNs(double* pValue);
    virtual void SetIllum(int* pValue);
    virtual void SetMap_Ka(std::string &pString);
    virtual void SetMap_Kd(std::string &pString);
    virtual void SetMap_Ks(std::string &pString);
    virtual void SetMap_Bump(std::string &pString);

    virtual const std::string GetName() const;
    virtual FbxDouble3& GetAmbient();
    virtual FbxDouble3& GetDiffuse();
    virtual FbxDouble3& GetSpecular();
    virtual FbxDouble& GetDissolve();
    virtual FbxDouble& GetHilight();
    virtual FbxInt& GetIllumModel();

protected:
    std::string     mName;
    FbxDouble3*     mKa;
    FbxDouble3*     mKd;
    FbxDouble3*     mKs;
    FbxDouble*      mD;
    FbxDouble*      mNs;
    FbxInt*         mIllum;
    std::string     mMap_Ka;
    std::string     mMap_Kd;
    std::string     mMap_Ks;
    std::string     mMap_Bump;
	ObjScene*       mScene;
};


#endif // !OBJMATERIAL_H
