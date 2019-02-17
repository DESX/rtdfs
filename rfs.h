#ifndef RFS_H
#define RFS_H
#define UUID_SIZE 16

//a device is a processor
//code can only be run on one device

struct rfs_device; 
//each device has a number of interfaces
struct rfs_interface; 
//each interface has a number of files 
struct rfs_file;
//each file has a sequence of events 
struct rfs_event;
//each event is of one of these types
enum{RFS_EVENT_OPEN,RFS_EVENT_UPDATE,RFS_EVENT_CLOSE};
enum{RFS_EVENT_DEVICE_CONNECTED,RFS_EVENT_DEVICE_NEW_ID,RFS_EVENT_DEVICE_DISCONNECTED};
//called when device is initialized
//uuid must be true universally unique id
struct rfs_device* rfs_new_device(char[UUID_SIZE]);
//adds new interface to device
//function pointer will be called to send data
struct rfs_interface* rfs_new_interface(struct rfs_device*,void (*send)(void*,unsigned int));
//called by the driver when data is received
struct rfs_receive(struct fts_interface*,void*,unsigned int);

//called every time file has an event
typedef void (*rfs_event_cb)(struct rfs_event*);
//returns device is
struct rfs_device * rfs_get_device(unsigned int); 

struct rfs_file * rfs_open(struct rfs_interface*, rfs_event_cb, unsigned int size, unsigned int id);

void              rfs_close(struct rfs_file *);
void              rfs_write(struct rfs_file*, void * data);
void              rfs_subscribe(struct rfs_file*);
void *            rfs_data(struct rfs_file*);
unsigned int      rfs_size(struct rfs_file*);

//the interface id is a unique number per each set of connected interfaces 
unsigned int      rfs_interface_id(struct rfs_interface*);
//each file has an id that is unique among all files on the interface
//all file ids for an interface are always consecutive

//the file id will change as files are added on the interface, and the file
//the file id always starts at zero and is re-assigned as needed as devices are added
//when a devices is connected to an interface, its id will change if there is already a device with the same id
//devices receive an id one greater than the most recently connected device
//when a device is disconnected from the interface, all newer devices will have their interface id's decremented
unsigned int      rfs_file_id(struct rfs_file*);
unsigned int      rfs_event_id(struct rfs_event*);

unsigned int            rfs_type(struct rfs_event*);
struct rfs_file *       rfs_file(struct rfs_event*);
struct rfs_interface*   rfs_interface(struct rfs_file*);
struct rfs_device   *   rfs_device(struct rfs_interface*);

#endif
