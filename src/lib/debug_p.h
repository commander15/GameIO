#ifndef GAMEIO_DEBUG_P_H
#define GAMEIO_DEBUG_P_H

#include <QtCore/qloggingcategory.h>

#define gameioDebug()    qCDebug(gameio).noquote().nospace()
#define gameioInfo()     qCInfo(gameio).noquote().nospace()
#define gameioWarning()  qCWarning(gameio).noquote().nospace()
#define gameioCritical() qCCritical(gameio).noquote().nospace()

Q_DECLARE_LOGGING_CATEGORY(gameio)

#endif // GAMEIO_DEBUG_P_H
