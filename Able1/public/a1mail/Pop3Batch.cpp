 // THIS CLASS IS OFFICIALLY OBSOLETE!
 
#include <a1mail/Pop3Batch.hpp>

using namespace BetterMail;

const char *POP3_RECOVERY_FILE = "zPop3Batch.Recovery";

const char *POP3_BATCH_FN        = "zPop3Batch.ARY";
const char *POP3_BATCH_ERROR_FN  = "zDownloadErrors.ARY";

// This is used to check article packets being hung-up on an "MORE/MORE".
// --Very usefull for general article query/resonse error tracking;
//#define MOO_MOO_CHECK 1
// This is used to "show" the logon process;


Pop3Batch::Pop3Batch(void) : bShouldDelete(true), ssNext(NULL), error_file_time(NULL), email_file_time(NULL)
   {
   ProgramId pid;
   Directory dir;
   pid.GetProgram(dir);
   sOutputDirectory = dir.Name();
   sOutputDirectory.Append("\\Pop3Batch");
   dir.Name(sOutputDirectory);
   dir.Create();
   }
Pop3Batch::~Pop3Batch(void)
   {
   }
bool Pop3Batch::Append(EMailMessage& em)
   {
   rArray[rArray.Nelem()] = em;
   return true;
   }
bool Pop3Batch::SaveRecoveryFile(void)
   {
   ProgramId pid;
   ZStr str = POP3_RECOVERY_FILE;
   File file;
   file.Name(str);
   pid.PutInTemp(file);
   ostream& os = file.OpenWrite(File::AT_BINARY);

   Array<StreamZStr> rReserved;
   rReserved.Write(os);

   rArray.Write(os);
   rErrorArray.Write(os);
   os.flush();
   if(os)
      return true;
   ::unlink(file.Name());
   return false;
   }
bool Pop3Batch::LoadRecoveryFile(void)
   {
   rArray.Free();
   rErrorArray.Free();

   ProgramId pid;
   ZStr str = POP3_RECOVERY_FILE;
   File file;
   file.Name(str);
   pid.PutInTemp(file);
   str = file.Name();

   istream& is = file.OpenRead(File::AT_BINARY);

   Array<StreamZStr> rReserved;
   rReserved.Read(is);

   rArray.Read(is);
   rErrorArray.Read(is);

   if(is)
      return true;
   return false;
   }
bool Pop3Batch::ShouldRecover(void)
   {
   File file;
   file.Name(POP3_RECOVERY_FILE);
   return file.Exists();
   }
size_t Pop3Batch::Save(void)
   {
   Directory dir;
   dir.Get();
   dir.Push();
   if(::SetCurrentDirectory(sOutputDirectory.c_str()) == 0)
      {
      dir.Pop();
      return NPOS;
      }

   for(size_t ss = NULL; ss < rArray.Nelem(); ss++)
      {
      File file;
      if(file.MkUniqueName() == false)
         return NPOS;
      if(EMailFactory::Export(file, rArray[ss]) == false)
         {
         dir.Pop();
         return NPOS;
         }
      }

   File file;
   file.Name("DownloadErrors.ARY");
   rErrorArray.Write(file.OpenAppend(File::AT_BINARY));

   dir.Pop();
   return rArray.Nelem();
   }
size_t Pop3Batch::Export(Directory& dirOut, const ZStr& sExt)
   {
   if(dirOut.Exists() == false)  // 02/01/2007 - 
      {
      if(dirOut.Create() == false)
         return npos;
      }
   Directory dir;
   dir.Get();
   dir.Push();

   if(dirOut.Set() == false)
      {
      dir.Pop();
      return NPOS;
      }
EMailMessage eml;
   ZStr sSubject;
   File file;
   for(size_t ss = NULL; ss < rArray.Nelem(); ss++)
      {
      file = EMailFactory::MkLocalName(dirOut, rArray[ss], sExt);
      if(EMailFactory::Export(file, rArray[ss]) == false)
         {
         dir.Pop();
         return NPOS;
         }
      }

   file.Name("DownloadErrors.ARY");
   rErrorArray.Write(file.OpenAppend(File::AT_BINARY));

   dir.Pop();
   return rArray.Nelem();
   }
size_t Pop3Batch::Dump(const ZStr& sExt)
   {
   Directory dir;
   dir.Get();
   dir.Push();
   if(::SetCurrentDirectory(sOutputDirectory.c_str()) == 0)
      {
      dir.Pop();
      return NPOS;
      }

   File file;
   for(size_t ss = NULL; ss < rArray.Nelem(); ss++)
      {
      if(file.MkUniqueName() == false)
         return NPOS;
      if(EMailFactory::Export(file, rArray[ss]) == false)
         {
         dir.Pop();
         return NPOS;
         }
      }

   file.Name("DownloadErrors.ARY");
   rErrorArray.Write(file.OpenAppend(File::AT_BINARY));

   dir.Pop();
   return rArray.Nelem();
   }
bool Pop3Batch::ReplaceArray(Array<EMailMessage>& rArray)
   {
   ZStr str;

   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_FN);
   File file;
   file.Name(str);
   ostream& os = file.OpenWrite(File::AT_BINARY);
   if(!os)
      return false;
   rArray.Write(os);
   if(os)
      {
      file.Close();
      email_file_time = file.GetTime();
      return true;
      }
   email_file_time = NULL;
   return false;
   }
bool Pop3Batch::HaveArraysChanged(void)
   {
   File file;
   ZStr str;

   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_ERROR_FN);
   file.Name(str);
   if(error_file_time && (error_file_time != file.GetTime()))
      return true;

   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_FN);
   file.Name(str);
   if(email_file_time && (email_file_time != file.GetTime()))
      return true;

   return false;
   }
bool Pop3Batch::ReplaceArray(Array<StreamZStr>& rArray)
   {
   ZStr str;

   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_ERROR_FN);
   File file;
   file.Name(str);
   ostream& os = file.OpenWrite(File::AT_BINARY);
   if(!os)
      return false;
   rArray.Write(os);
   if(os)
      {
      file.Close();
      error_file_time = file.GetTime();
      return true;
      }
   error_file_time = NULL;
   return false;
   }
bool Pop3Batch::LoadArray(Array<EMailMessage>& rArray)
   {
   ZStr str;
   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_FN);
   rArray.Free();

   File file;
   file.Name(str);
   email_file_time = file.GetTime();
   istream& is = file.OpenRead(File::AT_BINARY);
   if(!is)
      {
      file.Close();
      if(file.Exists() == false)    // The first time through, the file will NOT exist
         return true;               // so this in not a problem.
      return false;
      }
   rArray.Read(is);
   if(!is)
      return false;
   return true;
   }
bool Pop3Batch::LoadArray(Array<StreamZStr>& rArray)
   {
   ZStr str;
   str = sOutputDirectory;
   str.Append('\\');
   str.Append(POP3_BATCH_ERROR_FN);

   File file;
   file.Name(str);
   error_file_time = file.GetTime();
   istream& is = file.OpenRead(File::AT_BINARY);
   if(!is)
      return false;
   rArray.Read(is);
   if(!is)
      return false;
   return true;
   }
size_t Pop3Batch::SaveArrays(void)
   {
   bool br;
   br = ReplaceArray(rArray);
   if(br == false)
      return NPOS;
   br = ReplaceArray(rErrorArray);
   if(br == false)
      return NPOS;
   return rArray.Nelem();
   }
void Pop3Batch::BatchCompleted(void)
   {
   rArray.Free();
   rErrorArray.Free();
   ProgramId pid;
   ZStr str = POP3_RECOVERY_FILE;
   File file;
   file.Name(str);
   pid.PutInTemp(file);
   str = file.Name();
   ::unlink(str.c_str());
   }
bool Pop3Batch::AutoRemoveHostArticles(void)
   {
   return bShouldDelete;
   }
void Pop3Batch::Error(const ZStr& str)
   {
   rErrorArray[rErrorArray.Nelem()] = str;
   }
EMailMessage *Pop3Batch::Recall(EMailMessage *pem)
   {
   if(!pem)
      ssNext = NULL;
   if(ssNext < rArray.Nelem())
      {
      pem = &rArray[ssNext];
      ssNext++;
      }
   else
      pem = NULL;
   return pem;
   }
void Pop3Batch::RecallErrors(ZStr& str)
   {
   str = "";
   for(size_t ss = NULL; ss < rErrorArray.Nelem(); ss++)
      {
      str.Append(rErrorArray[ss]);
      str.Append("\r\n");
      }
   }
bool Pop3Batch::HadErrors(void)
   {
   if(rErrorArray.Nelem())
      return true;
   return false;
   }

 
