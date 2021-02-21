//using namespace tinyxml2;

#include "frame_mpk.h"
#include "HTTPClient.h"
#include "WiFi.h"
#include "tinyxml2.h"

#define CELL_W 4
#define CELL_H 4
#define CELL_X 135 + 2
#define CELL_Y 222 + 2


char * testDocument = "<root><element>7</element></root>";
//XMLDocument *xmlDocument = new XMLDocument();

tinyxml2::XMLDocument xmlDocument;


//static uint8_t mpk_cells_flag = 0;
M5EPD_Canvas mpk_cells_0(&M5.EPD);
M5EPD_Canvas mpk_cells_1(&M5.EPD);
M5EPD_Canvas mpk_canvas_0(&M5.EPD);
M5EPD_Canvas mpk_canvas_1(&M5.EPD);


void Mpk_RoundProcess()
{
    //if(lifegame_cells_flag == 0)
    //{
    //    for (int y = 1; y < CELL_Y - 1; y++)
    //    {
    //        for (int x = 1; x < CELL_X - 1; x++)
    //        {
    //            Mpk_CellProcess_0(x, y);
    //            lifegame_canvas_0.fillRect((x - 1) * CELL_W, (y - 1) * CELL_H, CELL_W, CELL_H, lifegame_cells_1.readPixel(x, y));
    //        }
    //    }
    //    lifegame_cells_flag = 1;
    //}
    //else
    //{
    //    for (int y = 1; y < CELL_Y - 1; y++)
    //    {
    //        for (int x = 1; x < CELL_X - 1; x++)
    //        {
    //            Mpk_CellProcess_1(x, y);
    //            lifegame_canvas_1.fillRect((x - 1) * CELL_W, (y - 1) * CELL_H, CELL_W, CELL_H, lifegame_cells_0.readPixel(x, y));
    //        }
    //    }
    //    lifegame_cells_flag = 0;
    //}
}

void Mpk_NextGen(void *pvParameters)
{
    Mpk_RoundProcess();
    vTaskDelete(NULL);
}

int Frame_Mpk::run()
{
    M5.update();

    if(xmlDocument.Parse(testDocument)!= tinyxml2::XML_SUCCESS)//
    {
        Serial.println("Error parsing");  
        return 1;
    };
    
    //if(M5.BtnP.wasReleased())
    //{
    //    Mpk_RandomCell();
    //}
    xTaskCreatePinnedToCore(Mpk_NextGen, "Mpk_NextGen", 4096, NULL, 1, NULL, 0);
    //if(lifegame_cells_flag == 0)
    //{
     //   lifegame_canvas_1.pushCanvas(0, 72, UPDATE_MODE_DU4);
    //}
    //else
    //{
    //    lifegame_canvas_0.pushCanvas(0, 72, UPDATE_MODE_DU4);
    //}
    log_d("");
    return 1;
}

void Frame_Mpk::exit()
{
    //lifegame_cells_0.deleteCanvas();
    //lifegame_cells_1.deleteCanvas();
    //lifegame_canvas_0.deleteCanvas();
    //lifegame_canvas_1.deleteCanvas();
}

Frame_Mpk::Frame_Mpk(void)
{
    _frame_name = "Frame_Mpk";
 
    uint8_t language = GetLanguage();
    if(language == LANGUAGE_JA)
    {
        exitbtn("ホーム");
        _canvas_title->drawString("ライフゲーム", 270, 34);
    }
    else if(language == LANGUAGE_ZH)
    {
        exitbtn("主页");
        _canvas_title->drawString("生命游戏", 270, 34);
    }
    else if(language == LANGUAGE_PL)
    {
        exitbtn("Powrot");
        _canvas_title->drawString("Mpk", 270, 34);
    }
    else
    {
        exitbtn("Home");
        _canvas_title->drawString("Mpk", 270, 34);
    }

    _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void*)(&_is_run));
    _key_exit->Bind(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);
}

Frame_Mpk::~Frame_Mpk(void)
{
}

int Frame_Mpk::init(epdgui_args_vector_t &args)
{
    String url = "http://lenic.eu";
    _is_run = 1;



    if (WiFi.status() != WL_CONNECTED)
    {
        log_e("Not connected");
        return 0;
    }

    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK)
    {
        log_e("HTTP ERROR: %d\n", httpCode);
        http.end();
        return 0;
    } else log_e("HTTP SUCCESS: %d\n", httpCode);


    //size_t size = http.getSize();

    //log_d("jpg size = %d Bytes", size);

    //WiFiClient *stream = http.getStreamPtr();
    //uint8_t *p = (uint8_t*)ps_malloc(size);
    //if(p == NULL)
    //{
    //    log_e("Memory overflow.");
    //    return 0;
   // }

    log_d("downloading...");
    //size_t offset = 0;
    //while (http.connected())
    //{
    //    size_t len = stream->available();
    //    if (!len)
    //    {
    //        delay(1);
    //        continue;
    //    }

    //    stream->readBytes(p + offset, len);
    //    offset += len;Mpk::init
   //     log_d("%d / %d", offset, size);
    //    if(offset == size)
    //    {
    //        break;
    //    }
    //}


    //lifegame_cells_1.createCanvas(CELL_X, CELL_Y);
    //lifegame_canvas_0.createCanvas(540, 888);
    //lifegame_canvas_1.createCanvas(540, 888);

    //lifegame_cells_0.fillCanvas(0);
    //lifegame_cells_1.fillCanvas(0);
    //lifegame_canvas_0.fillCanvas(0);
    //lifegame_canvas_1.fillCanvas(0);

    //lifegame_cells_0.pushImage(2, 2, 132, 120, ImageResource_lifegame_seeder_132x120);
    //lifegame_cells_flag = 0;

    M5.EPD.Clear();
    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);
    EPDGUI_AddObject(_key_exit);
    return 3;
}