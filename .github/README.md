This project presents using Docker environment with 
GitHub codespace environment


Run following commands in Codespace:
# docker image xv6_image prepare (. is for current directory): 
$ docker buld -t xv6_image .
# check docker images ID:
$ docker images
# run docker container:
$ docker run -it <docker image ID> 
# now yor can run ls command and see that only relevant files appear:
$ ls
# run xv6 without qemu window : 
$ make qemu-nox
# after xv6 starts to run, run ps command for example: 
$ ps


 
