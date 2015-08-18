#ifndef CPUINFOOBJECT_H
#define CPUINFOOBJECT_H




#include <QObject>

class CPUInfoObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString credit READ credit WRITE setCredit NOTIFY creditChanged)
    Q_PROPERTY(QString runrate READ runrate WRITE setRunrate NOTIFY runrateChanged)
    Q_PROPERTY(QString moredata READ moredata WRITE setMoredata NOTIFY moredataChanged)

public:
    CPUInfoObject(QObject *parent=0);
    CPUInfoObject(const QString &credit, const QString &runrate, const QString &moredata, QObject *parent=0);

    QString credit() const;
    void setCredit(const QString &credit);

    QString runrate() const;
    void setRunrate(const QString &runrate);

    QString moredata() const;
    void setMoredata(const QString &moredata);

signals:
    void creditChanged();
    void runrateChanged();
    void moredataChanged();

private:
    QString _credit;
    QString _runrate;
    QString _moredata;
};


#endif // CPUINFOOBJECT_H
