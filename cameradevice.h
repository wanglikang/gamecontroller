#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include <QObject>

class CameraDevice : public QObject
{
    Q_OBJECT
public:
    explicit CameraDevice(QObject *parent = 0);

signals:

public slots:
};

#endif // CAMERADEVICE_H