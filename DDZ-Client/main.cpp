#include "cards.h"
// #include "loading.h"
#include <QApplication>
#include <QResource>
#include "login.h"
#include <qDebug>
#include "aescrypto.h"
#include "rsacrypto.h"

void test()
{
    AesCrypto aes(AesCrypto::AES_CBC_128, "1234567887654321");
    QByteArray text = aes.encrypt("习近平强调，各级党委和政府要坚定不移贯彻落实党中央关于“三农”工作的决策部署，坚持农业农村优先发展，坚持城乡融合发展，把责任扛在肩上、抓在手上，结合实际创造性开展工作，有力有效推进乡村全面振兴，以加快农业农村现代化更好推进中国式现代化建设。");

    text = aes.decrypt(text);
    qDebug() << text.data();

    RsaCrypto rsa;
    rsa.generateRsaKey(RsaCrypto::BITS_2k);

    RsaCrypto rsa1("public.pem", RsaCrypto::PublicKey);
    // 可加密的最大数据长度 = bits/8-11;  11是填充
    QByteArray temp = "天长地久有时尽, 此恨绵绵无绝期!";
    temp = rsa1.pubKeyEncrypt(temp);
    qDebug() << "公钥加密的密文: " << temp;
    RsaCrypto rsa2("private.pem", RsaCrypto::PrivateKey);
    temp = rsa2.priKeyDecrypt(temp);
    qDebug() << temp.data();

    qDebug()<<"***********************";

    temp = rsa2.sign(text);
    qDebug() << "私钥签名的密文: " << temp;
    bool flag = rsa1.verify(temp, text);
    qDebug() << "flag = " << flag;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Cards>("Cards&");
    qRegisterMetaType<Cards>("Cards");
    // Loading w;
    // w.show();

    //test();

    Login w;
    w.show();

    return a.exec();
}
