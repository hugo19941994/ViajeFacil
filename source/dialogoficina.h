#ifndef DIALOGOFICINA_H
#define DIALOGOFICINA_H

#include <QDialog>
#include <vector>
#include "./oficina.hpp"
#include "./owner.hpp"
#ionclude "./pel_vector.hpp"

namespace Ui {
class DialogOficina;
}

class DialogOficina : public QDialog {
    Q_OBJECT

 public:
    explicit DialogOficina(QWidget *parent = 0);
    ~DialogOficina();
    void setOf (std::vector<Oficina>& ofi);
    void setOw(std::vector<Owner>& own);
    void cargar();

 private slots:

    void on_buttonBox_accepted();

    void on_comboBox_currentIndexChanged(int index);

 private:
    Ui::DialogOficina *ui;
    std::vector<Oficina> *of;
    std::vector<Owner> *ow;
};

#endif  // DIALOGOFICINA_H
