//---------------------------------------------------------------------------


#pragma hdrstop

#include "uStyle.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ZStr Style::sFileName = "style.css";


bool Style::Assert(const Directory& dir)
   {
   File file;
   if(file.Name(sFileName) == false)
      return false;
   if(dir.Home(file) == false)
      return false;

   if(file.Exists() == true)
      return true; // DO NOT overWrite- - could be user updated!

   ostream& os = file.OpenWrite();

   os << "BODY" << endl;
   os << "	{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	background-color:blue;" << endl;
   os << "	color:#014904;" << endl;
   os << "	text-align:justify" << endl;
   os << "	}" << endl;
   os << "H1" << endl;
   os << "	{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-weight:normal;" << endl;
   os << "	color:blue;" << endl;
   os << "	text-align:left" << endl;
   os << "	}" << endl;
   os << "H2" << endl;
   os << "	{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-size:large;" << endl;
   os << "	font-weight:normal;" << endl;
   os << "	color:red;" << endl;
   os << "	text-align:left" << endl;
   os << "	}" << endl;
   os << "B" << endl;
   os << "	{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-size:normal;" << endl;
   os << "	font-weight:heavy;" << endl;
   os << "	color:orange;" << endl;
   os << "	text-align:left" << endl;
   os << "	}" << endl;
   os << "TD" << endl;
   os << "	{" << endl;
   os << "	background-color:white;" << endl;
   os << "	}" << endl;
   os << ".header" << endl;
   os << "{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-size:small;" << endl;
   os << "	font-weight:heavy;" << endl;
   os << "	color:white;" << endl;
   os << "	background-color:#014904;" << endl;
   os << "	text-align:center" << endl;
   os << "}" << endl;
   os << ".body" << endl;
   os << "{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-size:small;" << endl;
   os << "	font-weight:normal;" << endl;
   os << "	color:#014904;" << endl;
   os << "	background-color:orange;" << endl;
   os << "	text-align:left" << endl;
   os << "}" << endl;
   os << ".footer" << endl;
   os << "{" << endl;
   os << "	font-family:Helvetica,Arial,sans-serif;" << endl;
   os << "	font-size:normal;" << endl;
   os << "	font-weight:normal;" << endl;
   os << "	color:#014904;" << endl;
   os << "	background-color:gray;" << endl;
   os << "	text-align:center" << endl;
   os << "}" << endl;

   return file.Exists();
   }
