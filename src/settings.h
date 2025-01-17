#ifndef SETTINGS_H
#define SETTINGS_H

#include "precompiled.h"
#include "camount.h"

using json = nlohmann::json;

struct Config {
    QString server;
};

struct ToFields;
struct Tx;

struct PaymentURI {
    QString addr;
    QString amt;
    QString memo;

    // Any errors are stored here
    QString error;
};

class Settings
{
public:
    static  Settings* init();
    static  Settings* getInstance();

    Config  getSettings();
    void    saveSettings(const QString& server);

    bool    isTestnet();
    void    setTestnet(bool isTestnet);
            
    bool    isSaplingAddress(QString addr);
    bool    isSproutAddress(QString addr);
            
    bool    isValidSaplingPrivateKey(QString pk);

    bool    isSyncing();
    void    setSyncing(bool syncing);

    int     gethushdVersion();
    void    sethushdVersion(int version);
    
    void    setUseEmbedded(bool r) { _useEmbedded = r; }
    bool    useEmbedded() { return _useEmbedded; }

    void    setHeadless(bool h) { _headless = h; }
    bool    isHeadless() { return _headless; }

    int     getBlockNumber();
    void    setBlockNumber(int number);
            
    bool    getAllowFetchPrices();
    void    setAllowFetchPrices(bool allow);

    bool    getCheckForUpdates();
    void    setCheckForUpdates(bool allow);

    QString get_theme_name();
    void set_theme_name(QString theme_name);

    bool    isSaplingActive();

    void    setZECPrice(double p) { ZECPrice = p; }
    double  getZECPrice();

    // Static stuff
    static const QString txidStatusMessage;
    
    static void saveRestore(QDialog* d);
    static void saveRestoreTableHeader(QTableView* table, QDialog* d, QString tablename) ;

    static void openAddressInExplorer(QString address);
    static void openTxInExplorer(QString txid);

    static PaymentURI parseURI(QString paymentURI);
    static QString    paymentURIPretty(PaymentURI);

    static bool    isZAddress(QString addr);
    static bool    isTAddress(QString addr);

    static QString getTokenName();
    static QString getDonationAddr();

    static QString getDefaultServer();
    static CAmount getMinerFee();

    static int     getMaxMobileAppTxns() { return 30; }

    static int     getNumberOfDecimalPlaces() {return 8;}
    
    static bool    isValidAddress(QString addr);

    static QString getChainName() { return QString("main"); }

    static const QString labelRegExp;

    static const int     updateSpeed         = 20 * 1000;        // 10 sec
    static const int     quickUpdateSpeed    = 5  * 1000;        // 3 sec
    static const int     priceRefreshSpeed   = 60 * 60 * 1000;   // 15 mins

private:
    // This class can only be accessed through Settings::getInstance()
    Settings() = default;
    ~Settings() = default;

    static Settings* instance;

    QString _executable;
    bool    _isTestnet        = false;
    bool    _isSyncing        = false;
    int     _blockNumber      = 0;
    int     _hushdVersion    = 0;
    bool    _useEmbedded      = false;
    bool    _headless         = false;
    
    double  ZECPrice          = 0.0;
};


inline bool isJsonResultSuccess(const json& res) {
    return res.find("result") != res.end() && 
                    QString::fromStdString(res["result"].get<json::string_t>()) == "success";
}

inline bool isJsonError(const json& res) {
    return res.find("error") != res.end();
}


#endif // SETTINGS_H
