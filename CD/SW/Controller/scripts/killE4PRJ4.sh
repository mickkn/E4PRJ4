#!/bin/bash

ps -ef | grep E4PRJ4 | grep -v grep | awk '{print $2}'| xargs kill -9
