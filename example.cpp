// ****************************************************************************
// NOTICE
//
// This work was produced for the U.S. Government under Contract 693KA8-22-C-00001
// and is subject to Federal Aviation Administration Acquisition Management System
// Clause 3.5-13, Rights In Data-General, Alt. III and Alt. IV (Oct. 1996).
//
// The contents of this document reflect the views of the author and The MITRE
// Corporation and do not necessarily reflect the views of the Federal Aviation
// Administration (FAA) or the Department of Transportation (DOT). Neither the FAA
// nor the DOT makes any warranty or guarantee, expressed or implied, concerning
// the content or accuracy of these views.
//
// For further information, please contact The MITRE Corporation, Contracts Management
// Office, 7515 Colshire Drive, McLean, VA 22102-7539, (703) 983-6000.
//
// (c) 2026 The MITRE Corporation. All Rights Reserved.
// ****************************************************************************

#include <iostream>
#include <string>

#include "loader/DecodedStream.h"
#include "loader/Loadable.h"

class ExampleBlock : public Loadable {
  public:
   bool load(DecodedStream *input) override {
      set_stream(input);
      register_var("varable_string", &varable_string, true);
      register_var("variable_read_with_cppuom", &variable_read_with_cppuom, true);
      return complete();
   }

   std::string varable_string;
   Units::MetersLength variable_read_with_cppuom{0.0};
};

class ExampleData : public Loadable {
  public:
   bool load(DecodedStream *input) override {
      set_stream(input);
      register_var("variable_double", &variable_double, true);
      register_var("variable_bool", &variable_bool, true);
      register_loadable_with_brackets("variable_block", &variable_block, true);
      return complete();
   }

   double variable_double{0.0};
   bool variable_bool{true};
   ExampleBlock variable_block;
};

int main(int argc, char *argv[])
{
    DecodedStream stream;
    if (!stream.open_file("example.txt")) {
        std::cerr << "Failed to open example.txt" << std::endl;
        return 1;
    }

    ExampleData data;
    if (!data.load(&stream) || data.variable_double != 1.0 || data.variable_bool ||
        data.variable_block.varable_string != "a_string" ||
        data.variable_block.variable_read_with_cppuom != Units::MetersLength(10.0)) {
        std::cerr << "example.txt validation failed" << std::endl;
        return 1;
    }

    std::cout << "example.txt loaded and validated" << std::endl;
    return 0;
}
