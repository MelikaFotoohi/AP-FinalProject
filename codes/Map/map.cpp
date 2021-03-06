#include "map.h"
#include "ui_map.h"

int tokenRandGnrt(int n){
   if (n >= 0 && n <= 4)
       return n + 2;
   else if (n >= 5 && n <= 9)
       return n + 3;

}

bool Map::tilesNumbers(int pixNum , QVector<int>tile_nums){
    if((pixNum <= 2 && tile_nums[pixNum] == 4 ) || (pixNum >= 3 && tile_nums[pixNum] == 3))
        return true;
    return false;
}

bool Map::tokenNumbers(int tokenNum , QVector<int> token_nums){
    if((tokenNum <= 8 && token_nums[tokenNum] == 2) ||  (tokenNum == 9 && token_nums[tokenNum] == 1))
        return true;
    return false;

}

/* make a random board */
void Map::randomMap(QVector<QPixmap> pixs,QVector<QPixmap> pixs_nums){
    QPixmap pix;
    QPixmap token;
    int pixNum;
    int tokenNum;
    QVector<int> tile_nums(5 , 0);
    QVector<int> token_nums(10 , 0);

    for(int i=0;i<19;i++){
        if(i!=15){
            pixNum = rand()%5;
            while(tilesNumbers(pixNum , tile_nums)){
                pixNum = rand()%5;
            }
            tile_nums[pixNum]++;
            pix = pixs[pixNum];
            QIcon icon(pix);
            labels[i]->setPixmap(pix);
            labels[i]->setMask(pix.mask());

            tokenNum = rand() % 10;
            while(tokenNumbers(tokenNum , token_nums)){
                tokenNum = rand() % 10;
            }
            token_nums[tokenNum]++;
            token  = pixs_nums[tokenNum];
            QIcon button_nums(token);
            tokens[i]->setIcon(button_nums);
            tokens[i]->setIconSize(pixs_nums[0].rect().size());

            Tile* tptr  = new Tile(TileType(pixNum),tokenRandGnrt(tokenNum),labels[i]);
            tiles.push_back(tptr);
        }else{
            QPixmap pixmap_16(":/new/prefix1/tiles/tile_desert.png");
            ui->label_16->setPixmap(pixmap_16);
            ui->label_16->setMask(pixmap_16.mask());
            Tile* tptr  = new Tile(TileType(5),0,labels[i]);
            tiles.push_back(tptr);
        }
    }
}



Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    srand(time(NULL));
    ui->setupUi(this);
    setWindowTitle("Board");

    QPixmap bkgnd(":/new/prefix1/backgrounds/sea.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    setFixedSize(1077 , 737);

    QPixmap pixmap_field(":/new/prefix1/tiles/tile_field.png");
    QPixmap pixmap_stone(":/new/prefix1/tiles/tile_stone.png");
    QPixmap pixmap_clay(":/new/prefix1/tiles/tile_clay.png");
    QPixmap pixmap_pasture(":/new/prefix1/tiles/tile_pasture.png");
    QPixmap pixmap_forest(":/new/prefix1/tiles/tile_forest.png");

    QPixmap pixmap_num2(":/new/prefix1/tiles_num/num_2.jpg");
    QPixmap pixmap_num3(":/new/prefix1/tiles_num/num_3.jpg");
    QPixmap pixmap_num4(":/new/prefix1/tiles_num/num_4.jpg");
    QPixmap pixmap_num5(":/new/prefix1/tiles_num/num_5.jpg");
    QPixmap pixmap_num6(":/new/prefix1/tiles_num/num_6.jpg");
    QPixmap pixmap_num8(":/new/prefix1/tiles_num/num_8.jpg");
    QPixmap pixmap_num9(":/new/prefix1/tiles_num/num_9.jpg");
    QPixmap pixmap_num10(":/new/prefix1/tiles_num/num_10.jpg");
    QPixmap pixmap_num11(":/new/prefix1/tiles_num/num_11.jpg");
    QPixmap pixmap_num12(":/new/prefix1/tiles_num/num_12.jpg");

    QPixmap pixmap_fieldPort(":/new/prefix1/ports/port_field.png");
    QPixmap pixmap_stonePort(":/new/prefix1/ports/port_stone.png");
    QPixmap pixmap_clayPort(":/new/prefix1/ports/port_clay.png");
    QPixmap pixmap_pasturePort(":/new/prefix1/ports/port_pasture.png");
    QPixmap pixmap_forestPort(":/new/prefix1/ports/port_forest.png");
    QPixmap pixmap_Port(":/new/prefix1/ports/port.png");

    QPixmap blue_person(":/new/prefix1/players/blue_person.png");
    QPixmap green_person(":/new/prefix1/players/green_person.png");
    QPixmap red_person(":/new/prefix1/players/red_person1.png");
    QPixmap yellow_person(":/new/prefix1/players/yellow_person.png");



    QIcon icon1(blue_person);
    ui->pushButton_149->setIcon(icon1);
    ui->pushButton_149->setIconSize(red_person.rect().size());

    QIcon icon2(green_person);
    ui->pushButton_148->setIcon(icon2);
    ui->pushButton_148->setIconSize(red_person.rect().size());

    QIcon icon3(red_person);
    ui->pushButton->setIcon(icon3);
    ui->pushButton->setIconSize(red_person.rect().size());

    QIcon icon4(yellow_person);
    ui->pushButton_147->setIcon(icon4);
    ui->pushButton_147->setIconSize(red_person.rect().size());


    ui->label_20->setPixmap(pixmap_Port);
    ui->label_20->setMask(pixmap_clayPort.mask());
    ui->label_21->setPixmap(pixmap_clayPort);
    ui->label_21->setMask(pixmap_clayPort.mask());
    ui->label_22->setPixmap(pixmap_fieldPort);
    ui->label_22->setMask(pixmap_fieldPort.mask());
    ui->label_23->setPixmap(pixmap_forestPort);
    ui->label_23->setMask(pixmap_forestPort.mask());
    ui->label_24->setPixmap(pixmap_stonePort);
    ui->label_24->setMask(pixmap_stonePort.mask());
    ui->label_25->setPixmap(pixmap_pasturePort);
    ui->label_25->setMask(pixmap_pasturePort.mask());

    QVector <QPixmap> pix_nums{pixmap_num2 , pixmap_num3 , pixmap_num4 , pixmap_num5 , pixmap_num6 ,
                               pixmap_num8 , pixmap_num9 , pixmap_num10 , pixmap_num11 , pixmap_num12};

    QVector<QPixmap> pixs {pixmap_field,pixmap_stone,pixmap_clay,pixmap_pasture,pixmap_forest};

    QVector<QLabel*> l {ui->label,ui->label_2,ui->label_3,ui->label_4,ui->label_5,ui->label_6,
                ui->label_7,ui->label_8,ui->label_9,ui->label_10,ui->label_11,ui->label_12,ui->label_13,
                ui->label_14,ui->label_15,ui->label_16,ui->label_17,ui->label_18,ui->label_19};
    labels = l;


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
    vertexsAvailable = vertexs;

    QVector<QPushButton*> e {ui->pushButton_20,ui->pushButton_21,ui->pushButton_76,ui->pushButton_77,ui->pushButton_78,ui->pushButton_79,ui->pushButton_80,
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
    edgesAvailable = edges;

    QVector<QPushButton*> t {ui->pushButton_4 , ui->pushButton_18 , ui->pushButton_14 , ui->pushButton_7 , ui->pushButton_8,
                ui->pushButton_17 , ui->pushButton_15 , ui->pushButton_19 , ui->pushButton_12 , ui->pushButton_11 , ui->pushButton_9,
                ui->pushButton_10 , ui->pushButton_5 , ui->pushButton_16,ui->pushButton_3 ,ui->pushButton_146 ,ui->pushButton_13 , ui->pushButton_2,
                ui->pushButton_6};
  //  ui->pushButton_146->setVisible(false);
    tokens = t;
    for(int i =0 ;i<tokens.size(); i++){
        tokens[i]->setEnabled(false);
    }
    robberToken = ui->pushButton_146;
    QPixmap pixmap_robber(":/new/prefix1/robber/1.png");
    ui->robber->setPixmap(pixmap_robber);
    ui->robber->setMask(pixmap_robber.mask());

    randomMap(pixs,pix_nums);
    setHide(vertexs);
    setHide(edges);

    QVector<QPair<tileType,QPair<QPushButton*,QPushButton*>>> p {{clay,{ui->pushButton_24,ui->pushButton_48}},
                                                                 {pasture,{ui->pushButton_34,ui->pushButton_70}},
                                                                 {stone,{ui->pushButton_44,ui->pushButton_29}},
                                                                 {forest,{ui->pushButton_26,ui->pushButton_30}},
                                                                 {field,{ui->pushButton_73,ui->pushButton_71}},
                                                                 {desert,{ui->pushButton_69,ui->pushButton_68}}};

    ports = p;


}

/* return settlements near ports*/
QVector<QPair<tileType,QPair<QPushButton*,QPushButton*>>> Map::getPorts(){
    return ports;
}

/* define tile's type */
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

/* unvisible pushbuttons */
void Map::setHide(QVector<QPushButton*> p){
    for(int i=0; i<p.size();i++){
        p[i]->setVisible(false);
    }
}

/* visible pushbuttons */
void Map::setUnHide(QVector<QPushButton*> p){
    for(int i=0; i<p.size();i++){
        p[i]->setVisible(true);
    }
}

/* available setllements */
QVector<QPushButton*> Map::getAvailableVertexs(){
    return vertexsAvailable;
}

/* available roads */
QVector<QPushButton*> Map::getAvailableEdges(){
    return edgesAvailable;
}

/* get tiles */
QVector<Tile*> Map::getTiles(){
    return tiles;
}

QVector<QPushButton*> Map::getTokens(){
    return tokens;
}

QPushButton* Map::getRobberToken(){
    return robberToken;
}

void Map::setRobberToken(QPushButton* p){
    robberToken = p;
}

/* remove vertex after putting a settlemet on it */
void Map::removeVertex(QPushButton* p){
    int i=0;
    for(;i<vertexsAvailable.size();i++){
        if(vertexsAvailable[i] == p)
            break;
    }
    vertexsAvailable.removeAt(i);
}

/* remove edge after putting a road on it */
void Map::removeEdge(QPushButton* p){
    int i=0;
    for(;i<edgesAvailable.size();i++){
        if(edgesAvailable[i] == p)
            break;
    }
    edgesAvailable.removeAt(i);
}


Map::~Map()
{
    delete ui;
}
