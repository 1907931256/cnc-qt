/****************************************************************************
 * Main developer, C# developing:                                           *
 * Copyright (C) 2014-2016 by Sergey Zheigurov                              *
 * Russia, Novy Urengoy                                                     *
 * zheigurov@gmail.com                                                      *
 *                                                                          *
 * C# to Qt portation, Linux developing                                     *
 * Copyright (C) 2015-2016 by Eduard Kalinowski                             *
 * Germany, Lower Saxony, Hanover                                           *
 * eduard_kalinowski@yahoo.de                                               *
 *                                                                          *
 * C# project CNC-controller-for-mk1                                        *
 * https://github.com/selenur/CNC-controller-for-mk1                        *
 *                                                                          *
 * The Qt project                                                           *
 * https://github.com/eduard-x/cnc-qt                                       *
 *                                                                          *
 * CNC-Qt is free software; may be distributed and/or modified under the    *
 * terms of the GNU General Public License version 3 as published by the    *
 * Free Software Foundation and appearing in the file LICENSE_GPLv3         *
 * included in the packaging of this file.                                  *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU Lesser General Public         *
 * License along with CNC-Qt. If not, see  http://www.gnu.org/licenses      *
 ****************************************************************************/

#include <QtGui>

#include "includes/mk1Controller.h"
#include "includes/Settings.h"


/******************************************************************************
** SettingsDialog
*/


SettingsDialog::SettingsDialog(QWidget *p)
    : QDialog(p)
{
    setupUi(this);

    parent = static_cast<MainWindow*>(p);

    cnc = parent->cnc;

    setStyleSheet(parent->programStyleSheet);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(onSave()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    checkXmin->setChecked(cnc->coord[X].limitMin);
    checkXplus->setChecked(cnc->coord[X].limitMax);
    checkYmin->setChecked(cnc->coord[Y].limitMin);
    checkYplus->setChecked(cnc->coord[Y].limitMax);
    checkZmin->setChecked(cnc->coord[Z].limitMin);
    checkZplus->setChecked(cnc->coord[Z].limitMax);
    checkAmin->setChecked(cnc->coord[A].limitMin);
    checkAplus->setChecked(cnc->coord[A].limitMax);

    checkSoftX->setChecked(cnc->coord[X].checkSoftLimits);
    doubleXmin->setValue(cnc->coord[X].softMin);
    doubleXmax->setValue(cnc->coord[X].softMax);

    checkSoftY->setChecked(cnc->coord[Y].checkSoftLimits);
    doubleYmin->setValue(cnc->coord[Y].softMin);
    doubleYmax->setValue(cnc->coord[Y].softMax);

    checkSoftZ->setChecked(cnc->coord[Z].checkSoftLimits);
    doubleZmin->setValue(cnc->coord[Z].softMin);
    doubleZmax->setValue(cnc->coord[Z].softMax);

    checkSoftA->setChecked(cnc->coord[A].checkSoftLimits);
    doubleAmin->setValue(cnc->coord[A].softMin);
    doubleAmax->setValue(cnc->coord[A].softMax);

    numPulseX->setValue(cnc->coord[X].pulsePerMm);
    numPulseY->setValue(cnc->coord[Y].pulsePerMm);
    numPulseZ->setValue(cnc->coord[Z].pulsePerMm);
    numPulseA->setValue(cnc->coord[A].pulsePerMm);

    doubleSpinStartX->setValue(cnc->coord[X].minVelo);
    doubleSpinStartY->setValue(cnc->coord[Y].minVelo);
    doubleSpinStartZ->setValue(cnc->coord[Z].minVelo);
    doubleSpinStartA->setValue(cnc->coord[A].minVelo);

    doubleSpinEndX->setValue(cnc->coord[X].maxVelo);
    doubleSpinEndY->setValue(cnc->coord[Y].maxVelo);
    doubleSpinEndZ->setValue(cnc->coord[Z].maxVelo);
    doubleSpinEndA->setValue(cnc->coord[A].maxVelo);

    doubleSpinAccelX->setValue(cnc->coord[X].acceleration);
    doubleSpinAccelY->setValue(cnc->coord[Y].acceleration);
    doubleSpinAccelZ->setValue(cnc->coord[Z].acceleration);
    doubleSpinAccelA->setValue(cnc->coord[A].acceleration);

    checkBoxDemoController->setChecked(cnc->DEMO_DEVICE);

    translateDialog();

    adjustSize();
}


void SettingsDialog::translateDialog()
{
    setWindowTitle(translate(_SETTINGS_TITLE));
    groupBoxImpulses->setTitle(translate(_PULSES_PER_MM));
    checkBoxDemoController->setText(translate(_DEV_SIMULATION));
    labelInfo->setText(translate(_DEV_SIM_HELP));

    labelStart->setText(translate(_STARTVELO));
    labelEnd->setText(translate(_ENDVELO));
    labelAcceleration->setText(translate(_ACCELERATION));

    QList<QAbstractButton*> l = buttonBox->buttons();
    QStringList strl = (QStringList() << translate(_OK) << translate(_CANCEL));

    for(int i = 0; i < l.count(); i++) {
        l[i]->setText(strl.at(i));
    }
}


void SettingsDialog::onSave()
{
    cnc->coord[X].limitMin = checkXmin->isChecked();
    cnc->coord[X].limitMax = checkXplus->isChecked();
    cnc->coord[Y].limitMin = checkYmin->isChecked();
    cnc->coord[Y].limitMax = checkYplus->isChecked();
    cnc->coord[Z].limitMin = checkZmin->isChecked();
    cnc->coord[Z].limitMax = checkZplus->isChecked();
    cnc->coord[A].limitMin = checkAmin->isChecked();
    cnc->coord[A].limitMax = checkAplus->isChecked();

    cnc->coord[X].checkSoftLimits = checkSoftX->isChecked();
    cnc->coord[X].softMin = doubleXmin->value();
    cnc->coord[X].softMax = doubleXmax->value();

    cnc->coord[Y].checkSoftLimits = checkSoftY->isChecked();
    cnc->coord[Y].softMin = doubleYmin->value();
    cnc->coord[Y].softMax = doubleYmax->value();

    cnc->coord[Z].checkSoftLimits = checkSoftZ->isChecked();
    cnc->coord[Z].softMin = doubleZmin->value();
    cnc->coord[Z].softMax = doubleZmax->value();

    cnc->coord[A].checkSoftLimits = checkSoftA->isChecked();
    cnc->coord[A].softMin = doubleAmin->value();
    cnc->coord[A].softMax = doubleAmax->value();

    cnc->coord[X].pulsePerMm = numPulseX->value();
    cnc->coord[Y].pulsePerMm = numPulseY->value();
    cnc->coord[Z].pulsePerMm = numPulseZ->value();
    cnc->coord[A].pulsePerMm = numPulseA->value();

    cnc->coord[X].minVelo = doubleSpinStartX->value();
    cnc->coord[Y].minVelo = doubleSpinStartY->value();
    cnc->coord[Z].minVelo = doubleSpinStartZ->value();
    cnc->coord[A].minVelo = doubleSpinStartA->value();

    cnc->coord[X].maxVelo = doubleSpinEndX->value();
    cnc->coord[Y].maxVelo = doubleSpinEndY->value();
    cnc->coord[Z].maxVelo = doubleSpinEndZ->value();
    cnc->coord[A].maxVelo = doubleSpinEndA->value();

    cnc->coord[X].acceleration = doubleSpinAccelX->value();
    cnc->coord[Y].acceleration = doubleSpinAccelY->value();
    cnc->coord[Z].acceleration = doubleSpinAccelZ->value();
    cnc->coord[A].acceleration = doubleSpinAccelA->value();

    cnc->DEMO_DEVICE  = checkBoxDemoController->isChecked();

    accept();
}

