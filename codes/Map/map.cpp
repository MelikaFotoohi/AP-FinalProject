#include "map.h"
#include "ui_map.h"
#include <QLabel>

tileType Map::TileType(int n){
    if (n==0)
        return field;
    if (n==1)
        return stone;
    if(n==2)
        return clay;
    if(n==3)
        return pasture;
    if(n==4)
        return forest;
    else
        return desert;
}

Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->centralWidget()->setStyleSheet( "background-image:url(\"/Users/macbook/Desktop/goli/AP_project/sea.jpeg\"); background-position: center;");
    //0_field
    QPixmap pixmap("/Users/macbook/Desktop/goli/AP_project/tile_field.png");
    //1_stone
    QPixmap pixmap_2("/Users/macbook/Desktop/goli/AP_project/tile_stone.png");
    //2_clay
    QPixmap pixmap_3("/Users/macbook/Desktop/goli/AP_project/tile_clay.png");
    //3_pasture
    QPixmap pixmap_5("/Users/macbook/Desktop/goli/AP_project/tile_pasture.png");
    //4_forest
    QPixmap pixmap_11("/Users/macbook/Desktop/goli/AP_project/image_2021-07-10_16-53-41.png");
    QVector<QPixmap> pixs {pixmap,pixmap_2,pixmap_3,pixmap_5,pixmap_11};
    QVector<QLabel*> labels {ui->label,ui->label_2,ui->label_3,ui->label_4,ui->label_5,ui->label_6,
                ui->label_7,ui->label_8,ui->label_9,ui->label_10,ui->label_11,ui->label_12,ui->label_13,
                ui->label_14,ui->label_15,ui->label_16,ui->label_17,ui->label_18,ui->label_19};
    QPixmap pix;
    int pixNum;
    srand(time(NULL));
    for(int i=0;i<19;i++){
        if(i!=15){
        pixNum = rand()%5;
        pix = pixs[pixNum];
        labels[i]->setPixmap(pix);
        labels[i]->setMask(pix.mask());
        Location* lptr = new Location(labels[i]->x(),labels[i]->y(),tile);
        Tile* tptr  = new Tile(TileType(pixNum),1,lptr);
        tiles.push_back(tptr);
        }else{
            QPixmap pixmap_16("/Users/macbook/Desktop/goli/AP_project/tDesert.png");
            ui->label_16->setPixmap(pixmap_16);
            ui->label_16->setMask(pixmap_16.mask());
            Location* lptr = new Location(labels[i]->x(),labels[i]->y(),tile);
            Tile* tptr  = new Tile(TileType(5),1,lptr);
            tiles.push_back(tptr);
        }
    }

}

Map::~Map()
{
    delete ui;
}
