#!/bin/bash

source venv/bin/activate
python3 generate_time_graph.py
deactivate
open time_graph.png