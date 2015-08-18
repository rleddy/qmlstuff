#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTableWidget>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>


#include "CPUInfoObject.h"




char *read_proc_file_cpuinfo() {

    char * arg;
    size_t size;

    FILE *fs = fopen("/proc/cpuinfo","rb");

    if ( fs ) {   // code from

        arg = NULL;

        while ( getdelim(&arg,&size,0,fs) != -1 ) {
            return(arg);
        }

        fclose(fs);

    }

    return(NULL);
}


/*
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 70
model name	: Intel(R) Core(TM) i7-4750HQ CPU @ 2.00GHz
stepping	: 1
microcode	: 0xf
cpu MHz		: 1995.345
cache size	: 6144 KB
physical id	: 0
siblings	: 1
core id		: 0
cpu cores	: 1
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts nopl xtopology tsc_reliable nonstop_tsc aperfmperf eagerfpu pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm ida arat epb xsaveopt pln pts dtherm fsgsbase tsc_adjust bmi1 avx2 smep bmi2 invpcid
bogomips	: 3990.69
clflush size	: 64
cache_alignment	: 64
address sizes	: 42 bits physical, 48 bits virtual
power management:
*/

void BuildCPUInfoDataList(QList<QObject*> &dataList) {

    char *data = read_proc_file_cpuinfo();

    if ( data ) {

        char *tmp = data;




        QString credit;
        QString HRZ;
        QString rest;


        while ( tmp ) {

            tmp = strstr(tmp,"processor");

            if ( tmp == NULL )  break;

            tmp += strlen("processor");
            tmp = strchr(tmp,'\n');
            if ( tmp ) {
                tmp++;
                tmp = strchr(tmp,':');
                if ( tmp ) {
                    tmp++;
                    while ( *tmp != '\n' ) {
                        credit += *tmp++;
                    }

                    tmp++;
                    while ( *tmp ) {
                        if ( strncmp(tmp, "cpu MHz", strlen("cpu MHz")) == 0 ) {

                            tmp = strchr(tmp,':');
                            if ( tmp ) {
                                while ( *tmp != '\n' ) {
                                    HRZ += *tmp++;
                                }
                            }

                        } else {
                            if ( *tmp == ':' ) { rest += ','; }
                            else if (  *tmp == '\n'  ) { rest += " | "; }
                            else {
                                if ( !isspace(*tmp) ) {
                                    rest += *tmp;
                                }
                            }
                        }

                        tmp++;
                    }

                }
            }

            dataList.append(new CPUInfoObject(credit, HRZ, rest));

        }

   }

}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QList<QObject*> dataList;
    BuildCPUInfoDataList(dataList);


    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("cpuInfoModel", QVariant::fromValue(dataList));

    view.setSource(QUrl("qrc:main.qml"));
    view.show();


    return app.exec();
}
