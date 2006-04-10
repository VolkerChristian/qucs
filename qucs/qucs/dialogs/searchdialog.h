/***************************************************************************
                               searchdialog.h
                              ----------------
    begin                : Sat Apr 01 2006
    copyright            : (C) 2006 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <qdialog.h>

class QucsApp;
class QLineEdit;
class QCheckBox;
class QPushButton;


class SearchDialog : public QDialog  {
Q_OBJECT
public:
  SearchDialog(QucsApp*);
 ~SearchDialog();

  void initSearch();
  void searchText(bool, int);

private slots:
  void slotSearch();

private:
  QucsApp *App;
  QLineEdit *SearchEdit;
  QCheckBox *PositionBox, *CaseBox, *WordBox, *BackwardBox;
};

#endif
