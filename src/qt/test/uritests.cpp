#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitmarkURI(uri, &rv));

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?dontexist="));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?label=Gamecredits Example Address"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString("Gamecredits Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?amount=0.001"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?amount=1.001"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?amount=100&label=Gamecredits Example"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Gamecredits Example"));

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?message=Gamecredits Example Address"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitmarkURI("gamecredits://bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?message=Gamecredits Example Address", &rv));
    QVERIFY(rv.address == QString("bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?req-message=Gamecredits Example Address"));
    QVERIFY(GUIUtil::parseBitmarkURI(uri, &rv));

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?amount=1,000&label=Gamecredits Example"));
    QVERIFY(!GUIUtil::parseBitmarkURI(uri, &rv));

    uri.setUrl(QString("gamecredits:bGfikGxWjawwxnBQSsinRZXFFQNSoudzk8?amount=1,000.0&label=Gamecredits Example"));
    QVERIFY(!GUIUtil::parseBitmarkURI(uri, &rv));
}
