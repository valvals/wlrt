#ifndef LIBRADTRAN_WRAPPER_H
#define LIBRADTRAN_WRAPPER_H

class QString;
class QStringList;

namespace lrt {

extern const char libradtran_input[];
extern const char libradtran_atmo_data_path[];
extern const char libradtran_solr_data_path[];
extern const char kLibradtran_input_path[];

void run_libradtran(double wls,
                    double wle,
                    double sza,
                    double phi, double umu,
                    double zout,
                    double phi0,
                    const QString& albedo_file,
                    const QString& solar_file,
                    const QString& atmo_file);
void run_libradtran();
void formatResult();
void getAtmosphereDataList(QStringList& atmo_list);
void getSolarDataList(QStringList& solar_list);
void getListOfData(const QString& path, QStringList& list);
QString getLastErrorsMessages();
}


#endif // LIBRADTRAN_WRAPPER_H
