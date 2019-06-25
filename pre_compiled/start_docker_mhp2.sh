#!/bin/bash

workdir=/opt/mhp2
docker_image=$1
net=$2

if [ -z $docker_image ]
then
	echo "usage: $0 docker_image_name network(main|dev|v8, default is main)"
	exit 2
fi


if [ -z "$net" ]
then
	net="main"
fi

echo $net

if [ ! -d $workdir ]
then
	mkdir -p $workdir
fi

cd $workdir

if [ ! -f settings.json.$net ]
then
	wget -q https://raw.githubusercontent.com/metahashorg/metahash-fullnode-client/master/pre_compiled/settings.json.$net

	if [ $? -ne 0 ]
	then
		echo failed to download config file for net $net
		exit 2
	fi
fi


docker run -it -p 9998:9999 -d -v $workdir/wallet.$net:/opt/mhservice/wallet -v $workdir/settings.json.$net:/opt/mhservice/settings.json -v $workdir/leveldb.$net:/opt/mhservice/leveldb.$net -v $workdir/blocks.$net:/opt/mhservice/blocks $docker_image
