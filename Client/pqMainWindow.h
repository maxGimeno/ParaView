/*
 * Copyright 2004 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */

#ifndef _pqMainWindow_h
#define _pqMainWindow_h

#include <QMainWindow>

class pqOptions;
class pqServer;

class pqMainWindow :
        public QMainWindow
{
  Q_OBJECT

public:
  pqMainWindow(QApplication& Application);
  
private:
  pqServer* const Server;

private slots:
  void onFileOpen();
  void onFileOpen(const QString& File);
  void onDebugHierarchy();
  void onTestsRun();
};

#endif // !_pqMainWindow_h

