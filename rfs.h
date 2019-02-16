#ifndef RFS_H
#define RFS_H
#define UUID_SIZE 16

//a device is a procssor
//code can only be run on one device
//code can only be run on one device

struct rfs_device; 
//each device has a number of interfaces
struct rfs_interface; 
//each interface has a numper of files 
struct rfs_file;
//each file has a sequence of events 
struct rfs_event;
//each event is of one of these types
enum{RFS_OPEN,RFS_UPDATE, RFS_CLOSE};

typedef void (*rfs_event_cb)(struct rfs_event*);

struct rfs_device * rfs_get_device(unsigned int); 

struct rfs_file * rfs_open(struct rfs_interface*, rfs_event_cb, unsigned int size, unsigned int id);

void              rfs_close(struct rfs_file *);
void              rfs_write(struct rfs_file*, void * data);
void              rfs_subscribe(struct rfs_file*);
void *            rfs_data(struct rfs_file*);
unsigned int      rfs_size(struct rfs_file*);

unsigned int      rfs_device_id(struct rfs_device*);
unsigned int      rfs_interface_id(struct rfs_interface*);
unsigned int      rfs_file_id(struct rfs_file*);
unsigned int      rfs_event_id(struct rfs_event*);

unsigned int            rfs_type(struct rfs_event*);
struct rfs_file *       rfs_file(struct rfs_event*);
struct rfs_interface*   rfs_interface(struct rfs_file*);
struct rfs_device   *   rfs_device(struct rfs_interface*);

#endif
