#include "map.h"
#include "ui_map.h"


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
void setUnVisible(QVector<QPushButton*> p){
    for(int i=0; i<p.size();i++){
        p[i]->setVisible(false);
    }
}
void setVisible(QVector<QPushButton*> p){
    for(int i=0; i<p.size();i++){
        p[i]->setVisible(true);
    }
}
QVector<tileType> Map::getAdjacent(QPushButton* p){
    QVector<tileType> tileAdj;
    for(int i=0;i<tiles.size();i++){
        if(abs((tiles[i]->getLocation()->getX()+60) - p->x() ) < 85 && abs((tiles[i]->getLocation()->getY()+70) - p->y() ) < 85 ){
            tileAdj.push_back(tiles[i]->getType());
            qDebug() << "ttiille" << i+1;
        }
    }
    return tileAdj;
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
    QVector<QLabel*> l {ui->label,ui->label_2,ui->label_3,ui->label_4,ui->label_5,ui->label_6,
                ui->label_7,ui->label_8,ui->label_9,ui->label_10,ui->label_11,ui->label_12,ui->label_13,
                ui->label_14,ui->label_15,ui->label_16,ui->label_17,ui->label_18,ui->label_19};
    labels = l;
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

    QVector<QPushButton*> v {ui->pushButton_22,ui->pushButton_23,ui->pushButton_24,ui->pushButton_25,ui->pushButton_26,
                ui->pushButton_27,ui->pushButton_28,ui->pushButton_29,ui->pushButton_30,ui->pushButton_31,ui->pushButton_32,
                ui->pushButton_33,ui->pushButton_34,ui->pushButton_35,ui->pushButton_36,ui->pushButton_37,ui->pushButton_38,
                ui->pushButton_39,ui->pushButton_40,ui->pushButton_41,ui->pushButton_42,ui->pushButton_43,ui->pushButton_44,
                ui->pushButton_45,ui->pushButton_46,ui->pushButton_47,ui->pushButton_48,ui->pushButton_49,ui->pushButton_50,
                ui->pushButton_51,ui->pushButton_52,ui->pushButton_53,ui->pushButton_54,ui->pushButton_55,ui->pushButton_56,
                ui->pushButton_57,ui->pushButton_58,ui->pushButton_59,ui->pushButton_60,ui->pushButton_61,ui->pushButton_62,
                ui->pushButton_63,ui->pushButton_64,ui->pushButton_65,ui->pushButton_66,ui->pushButton_67,ui->pushButton_68,
                ui->pushButton_69,ui->pushButton_70,ui->pushButton_71,ui->pushButton_72,ui->pushButton_73,ui->pushButton_74,
                ui->pushButton_75};
    vertexs = v;

    QVector<QPushButton*> e {ui->pushButton_76,ui->pushButton_77,ui->pushButton_78,ui->pushButton_79,ui->pushButton_80,
                ui->pushButton_81,ui->pushButton_82,ui->pushButton_83,ui->pushButton_84,ui->pushButton_85,ui->pushButton_86,
                ui->pushButton_87,ui->pushButton_88,ui->pushButton_89,ui->pushButton_90,ui->pushButton_91,ui->pushButton_92,
                ui->pushButton_93,ui->pushButton_94,ui->pushButton_95,ui->pushButton_96,ui->pushButton_97,ui->pushButton_98,
                ui->pushButton_99,ui->pushButton_100,ui->pushButton_101,ui->pushButton_102,ui->pushButton_103,ui->pushButton_104,
                ui->pushButton_105,ui->pushButton_106,ui->pushButton_107,ui->pushButton_108,ui->pushButton_109,ui->pushButton_110,
                ui->pushButton_111,ui->pushButton_112,ui->pushButton_113,ui->pushButton_114,ui->pushButton_115,ui->pushButton_116,
                ui->pushButton_117,ui->pushButton_118,ui->pushButton_119,ui->pushButton_120,ui->pushButton_121,ui->pushButton_122,
                ui->pushButton_123,ui->pushButton_124,ui->pushButton_125,ui->pushButton_126,ui->pushButton_127,ui->pushButton_128,
                ui->pushButton_129,ui->pushButton_130,ui->pushButton_131,ui->pushButton_132,ui->pushButton_133,ui->pushButton_134,
                ui->pushButton_135,ui->pushButton_136,ui->pushButton_137,ui->pushButton_138,ui->pushButton_139,ui->pushButton_140,
                ui->pushButton_141,ui->pushButton_142,ui->pushButton_143,ui->pushButton_144,ui->pushButton_145};

    edges = e;

    setUnVisible(vertexs);
    setUnVisible(edges);


    for(int i=0;i<vertexs.size();i++){
        qDebug() <<  "verteexx" << i+22;
        QVector<tileType> pb1 = getAdjacent(vertexs[i]);
        qDebug() << "\n";
    }
}

Map::~Map()
{
    delete ui;
}
