#ifndef GAMEIO_GLOBAL_H
#define GAMEIO_GLOBAL_H

#include <GameIO/config.h>

#ifdef GAMEIO_SHARED
#ifdef GAMEIO_BUILD
#   define GAMEIO_EXPORT Q_DECL_EXPORT
#else
#   define GAMEIO_EXPORT Q_DECL_IMPORT
#endif
#else
#   define GAMEIO_EXPORT
#endif

#define GAMEIO_D(ClassName) \
    ClassName##Private *d = static_cast<ClassName##Private *>(qGetPtrHelper(this->d))

#endif // GAMEIO_GLOBAL_H
