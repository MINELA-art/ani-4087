#include "compteur.h"
#include "test_compteur.h"

#ifdef __ANDROID__

// ----- Android : coquille native, elle ne fait encore qu'une chose -------------
// Remplir l'ecran d'une seule couleur, via une NativeActivity et EGL.
// Pas une ligne de Java : android_native_app_glue s'occupe du pont avec le
// systeme, Jenga le lie automatiquement pour toute activite native.

#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>

static EGLDisplay g_display = EGL_NO_DISPLAY;
static EGLSurface g_surface = EGL_NO_SURFACE;
static EGLContext g_context = EGL_NO_CONTEXT;

static void initDisplay(struct android_app* app) {
    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLint numConfigs, format;
    EGLConfig config;

    g_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(g_display, nullptr, nullptr);
    eglChooseConfig(g_display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(g_display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

    g_surface = eglCreateWindowSurface(g_display, config, app->window, nullptr);
    const EGLint ctxAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    g_context = eglCreateContext(g_display, config, nullptr, ctxAttribs);
    eglMakeCurrent(g_display, g_surface, g_surface, g_context);
}

static void drawColor() {
    // Bleu-vert de "projet_salle", coquille vide pour l'instant.
    glClearColor(0.05f, 0.45f, 0.40f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(g_display, g_surface);
}

static void onCmd(struct android_app* app, int32_t cmd) {
    if (cmd == APP_CMD_INIT_WINDOW && app->window != nullptr) {
        initDisplay(app);
        drawColor();
    }
}

void android_main(struct android_app* app) {
    app->onAppCmd = onCmd;

    int events;
    android_poll_source* source;
    while (true) {
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
            if (app->destroyRequested != 0) {
                return;
            }
        }
        if (g_display != EGL_NO_DISPLAY) {
            drawColor();
        }
    }
}

#else

// ----- Windows : la console de projet_salle, inchangee depuis l'exercice 5 -----
#include <iostream>
#include "moduleA.h"

int main() {
    int a = 5;
    int b = 7;

    int resultat = somme_plus_1000(a, b);

    std::cout << "somme_plus_1000(" << a << ", " << b << ") = " << resultat << std::endl;

    testerCompteur();

    return 0;
}

#endif
