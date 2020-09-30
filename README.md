[![builds.sr.ht status](https://builds.sr.ht/~tristan957/pigeon.svg)](https://builds.sr.ht/~tristan957/pigeon?)

# Pigeon

A GTK API Development Tool similar to Postman and Insomnia.

Pigeon is **under heavy development**.

Pigeon, the name, is an omage to WW2 carrier pigeons that would carry messages
to soldiers. In this case, we are sending messages to servers.

## Motivation

I am tired of Electron apps ruling my life.

#0  0x00007ffff7afd896 in gtk_widget_constructed (object=0x5bfac0) at ../subprojects/gtk-3.98.5/gtk/gtkwidget.c:881
#1  0x00007ffff75ef2e7 in g_object_new_internal () at /lib64/libgobject-2.0.so.0
#2  0x00007ffff75f06ad in g_object_new_with_properties () at /lib64/libgobject-2.0.so.0
#3  0x00007ffff75f1331 in g_object_new () at /lib64/libgobject-2.0.so.0
#4  0x0000000000404179 in pigeon_page_new () at ../src/pigeon-page.c:76
#5  0x0000000000403b1d in pigeon_application_window_init (self=0x5522e0) at ../src/pigeon-application-window.c:136
#6  0x00007ffff7609498 in g_type_create_instance () at /lib64/libgobject-2.0.so.0
#7  0x00007ffff75ef205 in g_object_new_internal () at /lib64/libgobject-2.0.so.0
#8  0x00007ffff75f0fac in g_object_new_valist () at /lib64/libgobject-2.0.so.0
#9  0x00007ffff75f130d in g_object_new () at /lib64/libgobject-2.0.so.0
#10 0x0000000000403f80 in pigeon_application_window_new (app=<optimized out>) at ../src/pigeon-application-window.c:145
#11 0x0000000000403981 in pigeon_application_activate (app=<optimized out>) at ../src/pigeon-application.c:41
#12 0x00007ffff75e9ae6 in _g_closure_invoke_va () at /lib64/libgobject-2.0.so.0
#13 0x00007ffff76026e9 in g_signal_emit_valist () at /lib64/libgobject-2.0.so.0
#14 0x00007ffff7602c63 in g_signal_emit () at /lib64/libgobject-2.0.so.0
#15 0x00007ffff7714518 in g_application_real_local_command_line () at /lib64/libgio-2.0.so.0
#16 0x00007ffff7714696 in g_application_run () at /lib64/libgio-2.0.so.0
#17 0x0000000000403611 in main (argc=1, argv=0x7fffffffccc8) at ../src/main.c:19
