#!/usr/bin/env python

import argparse
import os

NORMAL_APP_NAME = "template_app"
TEMPLATE_NAME = "app_name"
TITLE_APP_TEMPLATE = "{" + TEMPLATE_NAME.title() + "}"
UPPER_APP_TEMPLATE = "{" + TEMPLATE_NAME.upper() + "}"
NORMAL_APP_TEMPLATE = "{" + TEMPLATE_NAME + "}"
APP_TEMPLATE_PATH = "template_app"

def new_filename(fn, new_name):
    return fn.replace(NORMAL_APP_NAME, new_name)

def replace_template(file_content, new_string):
    file_content = file_content.replace(NORMAL_APP_TEMPLATE, new_string)
    file_content = file_content.replace(UPPER_APP_TEMPLATE, new_string.upper())
    file_content = file_content.replace(TITLE_APP_TEMPLATE,
                                        new_string.title().replace("_", ""))
    return file_content

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--name", help="Application name.", required=True)
    parser.add_argument("-o", "--output", help="Output directory.", default="../src/applications/")
    parsed_args = parser.parse_args()

    if not os.path.isdir(parsed_args.output):
        print("Error: Output must be an existing directory")
        return

    new_name = parsed_args.name.lower() + "_app"

    for curr_path, dirs, files in os.walk(APP_TEMPLATE_PATH):
        new_path = os.path.join(parsed_args.output,
                            curr_path.replace(APP_TEMPLATE_PATH, new_name))
        os.mkdir(new_path)
        for filename in files:
            new_file_path = os.path.join(new_path, new_filename(filename, new_name))
            with open(os.path.join(curr_path, filename)) as f:
                content = f.read()
            new_content = replace_template(content, new_name)
            with open(new_file_path, "w+") as f:
                f.write(new_content)

main()
