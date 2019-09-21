#ifndef __hellmakerpetcpr_H__
#define __hellmakerpetcpr_H__

#include <dlog.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif

#define LOG_TAG "HellMakerPetCpr"


#define ERR(fmt, args...	) dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s(%d) > " fmt" \n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define WARN(fmt, args...	) dlog_print(DLOG_WARN, LOG_TAG, "%s : %s(%d) > " fmt" \n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define INFO(fmt, args...	) dlog_print(DLOG_INFO, LOG_TAG, "%s : %s(%d) > " fmt" \n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define DBG(fmt, args...	) dlog_print(DLOG_DEBUG, LOG_TAG, "%s : %s(%d) > " fmt" \n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)



#ifdef __cplusplus
}
#endif

#endif /* __hellmakerpetcpr_H__ */
