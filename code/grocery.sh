#!/bin/sh

if [ "$#" -le 0 ]
then
  echo "$0: not enough arguments"
  exit 1
fi

if [ "$#" -gt 1 ]
then
  echo "$0: too many arguments"
  exit 1
fi

if [ ! -f "$1" ]
then
  echo "$0: file '$1' does not exist"
  exit 1
fi

person=""
unqueued="$(cat $1 | sort -R | while read name; do printf '%s' "$name" | base64; done)"
echo "$unqueued"
queued=""

get_name() {
  set -- $unqueued
  person="$1"
  shift
  unqueued="$@"
}

push_queue() {
  set -- $queued $person
  queued="$@"
}

pop_queue() {
  set -- $queued
  person="$1"
  shift
  queued="$@"
}

while [ -n "$unqueued" -o -n "$queued" ]
do
  if [ $((RANDOM % 2)) -eq 1 -a -n "$unqueued" ]
  then
    get_name
    echo "$(printf '%s' $person | base64 -d) gets in line."
    push_queue
  fi
  sleep 0.15

  if [ $((RANDOM % 2)) -eq 1 -a -n "$queued" ]
  then
    pop_queue
    echo "$(printf '%s' $person | base64 -d) finishes checking out."
  fi
  sleep 0.15
done
