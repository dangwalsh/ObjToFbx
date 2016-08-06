#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include "ObjScene.h"
#include <string>

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
    virtual void SetIllum(double* pValue);
    virtual void SetMap_Ka(std::string &pString);
    virtual void SetMap_Kd(std::string &pString);
    virtual void SetMap_Ks(std::string &pString);
    virtual void SetMap_Bump(std::string &pString);
    
    virtual std::string GetName() const;

protected:
    std::string     mName;
    double*         mKa;
    double*         mKd;
    double*         mKs;
    double*         mD;
    double*         mNs;
    double*         mIllum;
    std::string     mMap_Ka;
    std::string     mMap_Kd;
    std::string     mMap_Ks;
    std::string     mMap_Bump;
	ObjScene*       mScene;
};


#endif // !OBJMATERIAL_H