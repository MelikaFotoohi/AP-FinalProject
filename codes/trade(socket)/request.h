#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonArray>

enum tileType { field, stone, clay, pasture, forest, desert};

QT_BEGIN_NAMESPACE
namespace Ui {
class TCPSocket;
}
QT_END_NAMESPACE

class TCPSocket : public QMainWindow {
  Q_OBJECT
 private:
  QTcpSocket *socket;
  Ui::TCPSocket *ui;
  QMessageBox *message;
  int playerId;
  int clayBank = 4, forestBank = 4, stoneBank = 4, pastureBank = 4, fieldBank = 4;
  int fieldCard=0 , stoneCard=0, clayCard=0, pastureCard=0, forestCard=0;

 public:
  TCPSocket(QWidget *parent = nullptr); 
  ~TCPSocket();
  void connectToServer(void);
  void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);

 public slots:
  void send(void);
  void recieve(void);
  void backToPlayer();
  void TradeRequest(bool);
  void waitForCheckingConditions();
};
#endif  // TCPSOCKET_HPP
