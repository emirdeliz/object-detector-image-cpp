#!/bin/sh

# Initialize the docker-sync
docker-sync stop && docker-sync start && docker-compose up && build.sh