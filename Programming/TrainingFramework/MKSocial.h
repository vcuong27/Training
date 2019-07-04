#pragma once

#ifdef WIN32
	#include "../Utilities/utilities.h" 
#else
#include "../../Utilities/Math.h"
#include "Singleton.h"
#include<list>
#include <string>
#endif

enum TypeSNS
{
	NOSNS = 0,
	FACEBOOK,
	GOOGLE,
};


class MKSocial : public CSingleton<MKSocial>
{
private:
	bool		m_isLogin_FaceBook;
	bool		m_isLogin_Google;
public:
	MKSocial();
	~MKSocial();
	void		LoginSNS(TypeSNS sns);
	void		LogoutSNS(TypeSNS sns);
	bool		IsLogin(TypeSNS sns);
	void		ShareMessage(TypeSNS sns, std::string message);
};

