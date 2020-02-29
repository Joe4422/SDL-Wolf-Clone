#ifndef ERROR_H_
#define ERROR_H_

/******************************************************************************
 * Defines
 *****************************************************************************/
#define RETURN_STATUS_OK		return (MESSAGE){ STATUS_OK, "" }
#define THROW_ERROR(err, msg)	return (MESSAGE){ err, msg, __func__ }
#define TRY(err)				if (err.status != STATUS_OK) return err

#define MIN_REPORTED_ERR_LVL	(STATUS_MINOR_ERROR)

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef enum status
{
	STATUS_OK,
	STATUS_MINOR_ERROR,
	STATUS_ERROR,
	STATUS_CRITICAL_ERROR,
	STATUS_FAILURE
} STATUS;

typedef struct message
{
	const STATUS	status;
	const char *	msg;
	const char *	source;
} MESSAGE;

/******************************************************************************
 * Function declarations
 *****************************************************************************/
void Error_Handle(MESSAGE message);

#endif