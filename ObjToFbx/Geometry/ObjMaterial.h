#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include "ObjScene.h"
#include "ObjTex.h"
#include <string>
#include <fbxsdk.h>

class ObjScene;
class ObjTex;

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
    virtual void SetTex_Ka(ObjTex* pTexture);
    virtual void SetTex_Kd(ObjTex* pTexture);
    virtual void SetTex_Ks(ObjTex* pTexture);
    virtual void SetTex_Bump(ObjTex* pTexture);

    virtual std::string& GetName();
    virtual FbxDouble3& GetAmbient();
    virtual FbxDouble3& GetDiffuse();
    virtual FbxDouble3& GetSpecular();
	virtual FbxDouble3& GetTransparency();
    virtual FbxDouble& GetDissolve();
    virtual FbxDouble& GetHilight();
    virtual FbxInt& GetIllumModel();
    virtual ObjTex* GetAmbientTex();
    virtual ObjTex* GetDiffuseTex();
    virtual ObjTex* GetSpecularTex();
    virtual ObjTex* GetBumpTex();

protected:
    std::string mName;
    FbxDouble3* mKa;
    FbxDouble3* mKd;
    FbxDouble3* mKs;
	FbxDouble3* mTr;
    FbxDouble*  mD;
    FbxDouble*  mNs;
    FbxInt*     mIllum;
    ObjTex* mTex_Ka;
    ObjTex* mTex_Kd;
    ObjTex* mTex_Ks;
    ObjTex* mTex_Bump;
	ObjScene*   mScene;
};

enum ObjShader
{
    
};

#endif // !OBJMATERIAL_H
