#include "libradtran_wrapper.h"
#include "qclipboard.h"
#include "qguiapplication.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>

namespace lrt {

const  char libradtran_input[] = R"(
rte_solver sdisort
pseudospherical
number_of_streams 16
aerosol_default
output_user lambda uu

wavelength %1 %2
sza %3
albedo_file %4
phi %5
umu %6
zout %7
phi0 %8
source solar %9
atmosphere_file %10
)";

const char libradtran_atmo_data_path[] = "../data/atmmod/";
const char libradtran_solr_data_path[] = "../data/solar_flux/";
const char kLibradtran_input_path[] = "/libradtran/libradtran_2.0.4/libradtran.inp";

void run_libradtran(double wls,
                    double wle,
                    double sza,
                    double phi,
                    double umu,
                    double zout,
                    double phi0,
                    const QString &albedo_file,
                    const QString &solar_file,
                    const QString &atmo_file) {
  const QString  libradtran_path = QDir::currentPath() + "/libradtran/libradtran.bat";
  QFile file("libradtran/libradtran_2.0.4/libradtran.inp");
  file.open(QIODevice::WriteOnly);
  QString input((QString(libradtran_input)));
  input = input.arg(wls).arg(wle).arg(sza).arg(albedo_file).arg(phi).arg(umu).arg(zout).arg(phi0).arg(solar_file).arg(atmo_file);
  file.write(QString(input).toLatin1());
  file.close();
  std::system(libradtran_path.toStdString().c_str());
}

void run_libradtran()
{
  const QString  libradtran_path = QDir::currentPath() + "/libradtran/libradtran.bat";
  std::system(libradtran_path.toStdString().c_str());
}

void formatResult()
{
  QString result;
  const QString out_file_name = QDir::currentPath()+"/libradtran/_out/libradtran.txt";
  QFile file(out_file_name);
  file.open(QIODevice::ReadOnly);
  QTextStream ts(&file);
  while(!ts.atEnd()){
    auto line = ts.readLine();
    if(line.isEmpty())continue;
    auto elements = line.split(' ');
    elements.removeAll("");
    if(elements.size() != 2)continue;;
    result.append(elements[0]);
    result.append("\t");
    result.append(QString::number(elements[1].toDouble()*1000000));
    result.append("\n");
  }
  file.close();
  QFile::remove(out_file_name);
  file.open(QIODevice::WriteOnly);
  file.write(result.toLatin1());
  file.close();
  QClipboard* clipboard = QGuiApplication::clipboard();
  clipboard->setText(result);
}

void getAtmosphereDataList(QStringList &atmo_list)
{
  getListOfData(QDir::currentPath()+"/libradtran/data/atmmod", atmo_list);
}

void getSolarDataList(QStringList& solar_list)
{
  getListOfData(QDir::currentPath()+"/libradtran/data/solar_flux", solar_list);
}

void getListOfData(const QString& path,
                   QStringList& list)
{
  if(!list.isEmpty())list.clear();
  QDir dir;
  dir.setPath(path);
  QStringList filters = {"*.dat"};
  dir.setNameFilters(filters);
  list = dir.entryList();
  qDebug()<<path;
  qDebug()<<"--->"<<list;
}

} // end lrt namespace