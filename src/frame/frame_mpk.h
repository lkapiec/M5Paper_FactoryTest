#ifndef _FRAME_MPK_H_
#define _FRAME_MPK_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"
#include <tinyxml2.h>


class Frame_Mpk : public Frame_Base
{
public:
    Frame_Mpk();
    ~Frame_Mpk();
    int init(epdgui_args_vector_t &args);
    int run();
    void exit();

private:
    M5EPD_Canvas *cells_0;
    M5EPD_Canvas *cells_1;
    M5EPD_Canvas *canvas_0;
    M5EPD_Canvas *canvas_1;
};

#endif //_FRAME_LIFEGAME_H_