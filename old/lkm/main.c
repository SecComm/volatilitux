
#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>     // Needed for the macros

#include <linux/sched.h>
#include <linux/fs.h>

#define CONFIG_VERSION "1.0"

#define GEN_LINE(...) \
  printk(KERN_INFO __VA_ARGS__)
  
  
#define GEN_BEGIN_CONFIG()\
  GEN_LINE("<config version = \"%s\">\n\n", CONFIG_VERSION)
  
#define GEN_END_CONFIG()\
  GEN_LINE("</config>\n")

  
#define GEN_F1(S, FIELD) \
  GEN_LINE("<field name = \"%s\" offset = \"%d\" />\n", # FIELD, offsetof(struct S, FIELD))
  
#define GEN_F2(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F1(S, __VA_ARGS__)
  
#define GEN_F3(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F2(S, __VA_ARGS__)
  
#define GEN_F4(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F3(S, __VA_ARGS__)
  
#define GEN_F5(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F4(S, __VA_ARGS__)
  
#define GEN_F6(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F5(S, __VA_ARGS__)
  
#define GEN_F7(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F6(S, __VA_ARGS__)
  
#define GEN_F8(S, FIELD, ...) \
  GEN_F1(S, FIELD); \
  GEN_F7(S, __VA_ARGS__)
  
  
#define GEN_FN(NB, ...) \
  GEN_F ## NB(__VA_ARGS__)


#define GEN_BEGIN_STRUCT(S) \
  GEN_LINE("<struct name = \"%s\" size = \"%d\">\n", # S, sizeof(struct S)) \
  
#define GEN_END_STRUCT() \
  GEN_LINE("</struct>\n\n")

#define GEN_STRUCT(NB, S, ...) \
  GEN_BEGIN_STRUCT(S); \
  GEN_FN(NB, S, __VA_ARGS__); \
  GEN_END_STRUCT()



static int module_load(void) {
  GEN_LINE("#######################################\n");
  GEN_LINE("# Volatilightux Confgen module loaded #\n");
  GEN_LINE("#######################################\n");
  
  GEN_LINE("init_task is at 0x%08x\n", __pa(&init_task));
  
  GEN_BEGIN_CONFIG();
  
  //Tasks
  GEN_STRUCT(4, task_struct, pid, comm, tasks, mm);
  
  //Virtual memory spaces
  GEN_STRUCT(2, mm_struct, mmap, pgd);
  
  //Virtual memory areas
  GEN_STRUCT(7, vm_area_struct, vm_mm, vm_start, vm_end, vm_pgoff, vm_file, vm_next, vm_flags);
  
  //Files
  GEN_STRUCT(1, file, f_path);
  GEN_STRUCT(1, path, dentry);
  GEN_STRUCT(1, dentry, d_name);
  GEN_STRUCT(1, qstr, name);
  
  GEN_END_CONFIG();

  //Must return 0, otherwise the module is not loaded
  return 0;
}

static void module_unload(void) {
  GEN_LINE("##########################################\n");
  GEN_LINE("# Volatilightux Confgen module unloaded. #\n");
  GEN_LINE("##########################################\n\n");
}  

module_init(module_load);
module_exit(module_unload);

