#ifdef ANDROID
#include <jni.h>
#include <stdio.h>
#include <sys/time.h>
#include "Application.h"
#include "Vertex.h"
#include "Shaders.h"
#include <string>

void LoginGameAPI();
void LogoutGameAPI();
bool isLoginGameAPI();
void ShareGameAPI(std::string text);
void LoginFaceBook();
void LogoutFaceBook();
bool isLoginFaceBook();
void ShareFaceBook(std::string text);

JNIEnv* mEnv = NULL;
jclass clazz = NULL;


GLint screenWidth = 640;
GLint screenHeight = 720;
static unsigned int s_current_time = 0;
static unsigned int s_delta_time = 0;
static unsigned int s_time = 0;

unsigned int getTime(void)
{
    struct timeval  now;
    gettimeofday(&now, NULL);
    return (now.tv_sec*1000 + now.tv_usec/1000);
}

	#define GAME Game::GetInstance()

int setupGraphics(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
	Application::GetInstance()->Init();
	return 0;
}

extern "C" {
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Init(JNIEnv * env, jobject obj,  jint width, jint height);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Rotation(JNIEnv * env, jobject obj,  jint type);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Move(JNIEnv * env, jobject obj,  jint type);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Step(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_ChangeEffect(JNIEnv * env, jobject obj, jint effect);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_TouchEvent(JNIEnv * env, jobject obj, jint bIsPresseded, jint x, jint y);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_KeyEvent(JNIEnv * env, jobject obj, jint bIsPresseded, jint key);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	mEnv = env;
	struct timeval start;
	setupGraphics(width, height);
	//LoginGameAPI();
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Rotation(JNIEnv * env, jobject obj,  jint type)
{
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Move(JNIEnv * env, jobject obj,  jint type)
{
	s_time++;
	if(s_time<5)
		return;
	s_time = 0;

	LOGD("Java_com_android_gl2jni_GL2JNILib_Move type = %d", type);
	switch (type)
	{
	case 1 :
		Application::GetInstance()->HandleKeyEvent( KEY_UP, true);
		break;
	case 2 :
		Application::GetInstance()->HandleKeyEvent( KEY_DOWN, true);
		break;
	case 3 :
		Application::GetInstance()->HandleKeyEvent( KEY_LEFT, true);
		break;
	case 4 :
		Application::GetInstance()->HandleKeyEvent( KEY_RIGHT, true);
		break;

	default:
		//Application::GetInstance()->HandleKeyEvent( KEY_UP, true);
		//Application::GetInstance()->HandleKeyEvent( KEY_DOWN, true);
		break;
	}

	
}


JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_Step(JNIEnv * env, jobject obj)
{
	int time = getTime();	
	if(s_current_time != 0)	
		s_delta_time = time - s_current_time;
	s_current_time = time;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Application::GetInstance()->Update((float)s_delta_time/(float)1000);
	Application::GetInstance()->Render();

}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_ChangeEffect(JNIEnv * env, jobject obj, jint effect)
{
	
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_TouchEvent(JNIEnv * env, jobject obj, jint bIsPresseded, jint x, jint y)
{
	LOGD("Java_com_android_gl2jni_GL2JNILib_touch x = %d, y =%d, IsPresseded = %d", x, y, bIsPresseded);
	Application::GetInstance()->HandleTouchEvent(x,y,true);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_KeyEvent(JNIEnv * env, jobject obj, jint bIsPresseded, jint key)
{

}


void LoginGameAPI()
{
	LOGD("LoginGameAPI");
	clazz = (jclass)mEnv->FindClass("com/android/gl2jni/GL2JNIActivity");
    if (clazz == 0) {
        LOGI("FindClass error");
        return;
    }
    jmethodID javamethod = mEnv->GetStaticMethodID(clazz, "LoginGameAPI", "()V");
    if (javamethod == 0) {
        LOGI("GetMethodID error");
        return;
    }
    mEnv->CallStaticVoidMethod(clazz, javamethod);
}


void LogoutGameAPI()
{
	LOGD("LogoutGameAPI");
	clazz = (jclass)mEnv->FindClass("com/android/gl2jni/GL2JNIActivity");
    if (clazz == 0) {
        LOGI("FindClass error");
        return;
    }
    jmethodID javamethod = mEnv->GetStaticMethodID(clazz, "LogoutGameAPI", "()V");
    if (javamethod == 0) {
        LOGI("GetMethodID error");
        return;
    }
    mEnv->CallStaticVoidMethod(clazz, javamethod);
}

bool isLoginGameAPI()
{
	return 0;
}

void ShareGameAPI(std::string text)
{

}

void LoginFaceBook()
{
	LOGD("LoginFaceBook");
	clazz = (jclass)mEnv->FindClass("com/android/gl2jni/GL2JNIActivity");
    if (clazz == 0) {
        LOGI("FindClass error");
        return;
    }
    jmethodID javamethod = mEnv->GetStaticMethodID(clazz, "LoginFaceBook", "()V");
    if (javamethod == 0) {
        LOGI("GetMethodID error");
        return;
    }
    mEnv->CallStaticVoidMethod(clazz, javamethod);
}


void LogoutFaceBook()
{
	LOGD("LogoutFaceBook");
	clazz = (jclass)mEnv->FindClass("com/android/gl2jni/GL2JNIActivity");
    if (clazz == 0) {
        LOGI("FindClass error");
        return;
    }
    jmethodID javamethod = mEnv->GetStaticMethodID(clazz, "LogoutFaceBook", "()V");
    if (javamethod == 0) {
        LOGI("GetMethodID error");
        return;
    }
    mEnv->CallStaticVoidMethod(clazz, javamethod);
}


bool isLoginFaceBook()
{
	return 0;
}
void ShareFaceBook(std::string text)
{
}

#endif