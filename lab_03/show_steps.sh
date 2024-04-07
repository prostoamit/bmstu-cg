#!/bin/bash

source venv/bin/activate
python3 generate_steps_graph.py
deactivate
open steps_graph.png