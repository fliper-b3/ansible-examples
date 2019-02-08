#!/bin/bash

openssl genrsa -out priv 4096 && openssl rsa -in priv -pubout -out pub
