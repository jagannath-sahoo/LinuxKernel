# Module Parameter Macros

1. module_param()
    * module_param(name, type, perm)
    To initialize the arguments\
        name: variable name\
        type: datatype\
        permisssion: S_IWUSR, S_IRUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP
2. module_param_array()
    * module_param_array(name,type,num,perm);
        name is the name of your array (and of the parameter),\ 
        type is the type of the array elements, \
        num is an integer variable (optional) otherwise NULL 
        perm is the usual permissions value.
3. module_param_cb()
    * module_param_cb(variable_name, &param_ops, &variable_name, perm)
    variable_name is the name of variable\
    **struct kernel_param_ops** Structure to provide callback method \
    &variable_name is the pointer address to variable name \
    perm is the usual permissions value.

**insmod KernelModuleProvidePram.ko uVal=10 sName="SIPU" uArr_Val=100,200,300,400**

**echo 1000  > /sys/module/KernelModuleProvidePram/parameters/uCBValue**