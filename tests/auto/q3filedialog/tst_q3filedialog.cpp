/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#include <qapplication.h>
#include <qdebug.h>
#include <q3filedialog.h>
#include <qlabel.h>

//TESTED_CLASS=
//TESTED_FILES=

class tst_Q3FileDialog : public QObject
{
Q_OBJECT

public:
    tst_Q3FileDialog();
    virtual ~tst_Q3FileDialog();

private slots:
#ifndef QT_MAC_USE_COCOA
    void getSetCheck();
#endif
};

tst_Q3FileDialog::tst_Q3FileDialog()
{
}

tst_Q3FileDialog::~tst_Q3FileDialog()
{
}

#ifndef QT_MAC_USE_COCOA
  class Preview : public QLabel, public Q3FilePreview
  {
  public:
      Preview(QWidget *parent=0) : QLabel(parent) {}

      void previewUrl(const Q3Url &u)
      {
          QString path = u.path();
          QPixmap pix(path);
          if (pix.isNull())
              setText("This is not a pixmap");
          else
              setText("This is a pixmap");
      }
  };


// Testing get/set functions
void tst_Q3FileDialog::getSetCheck()
{
    Q3FileDialog obj1;
    // bool Q3FileDialog::showHiddenFiles()
    // void Q3FileDialog::setShowHiddenFiles(bool)
    obj1.setShowHiddenFiles(false);
    QCOMPARE(false, obj1.showHiddenFiles());
    obj1.setShowHiddenFiles(true);
    QCOMPARE(true, obj1.showHiddenFiles());

    // ViewMode Q3FileDialog::viewMode()
    // void Q3FileDialog::setViewMode(ViewMode)
    obj1.setViewMode(Q3FileDialog::ViewMode(Q3FileDialog::Detail));
    QCOMPARE(obj1.viewMode(), Q3FileDialog::ViewMode(Q3FileDialog::Detail));
    obj1.setViewMode(Q3FileDialog::ViewMode(Q3FileDialog::List));
    QCOMPARE(obj1.viewMode(), Q3FileDialog::ViewMode(Q3FileDialog::List));

    Preview* p = new Preview;
    obj1.setContentsPreviewEnabled(true);
    obj1.setContentsPreview(p, p);
    obj1.setInfoPreviewEnabled(true);
    obj1.setInfoPreview(p, p);
    // PreviewMode Q3FileDialog::previewMode()
    // void Q3FileDialog::setPreviewMode(PreviewMode)
    obj1.setPreviewMode(Q3FileDialog::PreviewMode(Q3FileDialog::NoPreview));
    QCOMPARE(obj1.previewMode(), Q3FileDialog::PreviewMode(Q3FileDialog::NoPreview));

    obj1.setContentsPreviewEnabled(true);
    obj1.setInfoPreviewEnabled(false);
    obj1.setPreviewMode(Q3FileDialog::PreviewMode(Q3FileDialog::Contents));
    QCOMPARE(obj1.previewMode(), Q3FileDialog::PreviewMode(Q3FileDialog::Contents));

    obj1.setInfoPreviewEnabled(true);
    obj1.setContentsPreviewEnabled(false);
    obj1.setPreviewMode(Q3FileDialog::PreviewMode(Q3FileDialog::Info));
    QCOMPARE(obj1.previewMode(), Q3FileDialog::PreviewMode(Q3FileDialog::Info));
}
#endif

QTEST_MAIN(tst_Q3FileDialog)
#include "tst_q3filedialog.moc"
