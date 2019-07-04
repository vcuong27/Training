#include "stdafx.h"
#include "MKSocial.h"

#ifdef ANDROID
extern void LoginGameAPI();
extern void LogoutGameAPI();
extern bool isLoginGameAPI();
extern void ShareGameAPI(std::string text);
extern void LoginFaceBook();
extern void LogoutFaceBook();
extern bool isLoginFaceBook();
extern void ShareFaceBook(std::string text);
#else
void LoginGameAPI(){}
void LogoutGameAPI(){}
bool isLoginGameAPI(){ return 0;}
void ShareGameAPI(std::string text){}
void LoginFaceBook(){}
void LogoutFaceBook(){}
bool isLoginFaceBook(){ return 0;}
void ShareFaceBook(std::string text){}
#endif // ANDROID



MKSocial::MKSocial(void)
{
}


MKSocial::~MKSocial(void)
{
}


void MKSocial::LoginSNS(TypeSNS sns)
{
	switch (sns)
	{
	case NOSNS:
		break;
	case FACEBOOK:
		LoginFaceBook();
		break;
	case GOOGLE:
		LoginGameAPI();
		break;
	default:
		break;
	}
}

void MKSocial::LogoutSNS(TypeSNS sns)
{
	switch (sns)
	{
	case NOSNS:
		break;
	case FACEBOOK:
		LogoutFaceBook();
		break;
	case GOOGLE:
		LogoutGameAPI();
		break;
	default:
		break;
	}
}

bool MKSocial::IsLogin(TypeSNS sns)
{
	switch (sns)
	{
	case NOSNS:
		break;
	case FACEBOOK:
		return isLoginGameAPI();
		break;
	case GOOGLE:
		return isLoginFaceBook();
		break;
	default:
		break;
	}
	return false;
}

void MKSocial::ShareMessage(TypeSNS sns, std::string message)
{
	switch (sns)
	{
	case NOSNS:
		break;
	case FACEBOOK:
		ShareFaceBook(message);
		break;
	case GOOGLE:
		ShareGameAPI(message);
		break;
	default:
		break;
	}
}
