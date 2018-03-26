@echo off
if "%1" == "" goto error
call hotswap %1 .append = .Append
call hotswap %1 .as_int = .AsInt
call hotswap %1 .as_long = .AsLong
call hotswap %1 .assign = .Assign
call hotswap %1 .cmp = .Cmp
call hotswap %1 .copy_bytes = .CopyBytes
call hotswap %1 .copy_pos = .CopyPos
call hotswap %1 .ends_with = .EndsWith
call hotswap %1 .enumerate = .Enumerate
call hotswap %1 .equals = .Equals
call hotswap %1 .find = .Find
call hotswap %1 .find_any = .FindAny
call hotswap %1 .find_last = .FindLast
call hotswap %1 .get_token = .GetToken
call hotswap %1 .insert = .Insert
call hotswap %1 .iomax = .Iomax
call hotswap %1 .is_alnum = .IsAlnum
call hotswap %1 .is_alpha = .IsAlpha
call hotswap %1 .is_ascii = .IsAscii
call hotswap %1 .is_null = .IsNull
call hotswap %1 .is_space = .IsSpace
call hotswap %1 .is_white = .IsWhite
call hotswap %1 .length = .Length
call hotswap %1 .mk_white = .MkWhite
call hotswap %1 .mkwhite = .MkWhite
call hotswap %1 .own = .Own
call hotswap %1 .prepend = .Prepend
call hotswap %1 .readline = .Readline
call hotswap %1 .read_line = .ReadLine
call hotswap %1 .read_stream = .ReadStream
call hotswap %1 .read_string = .ReadString
call hotswap %1 .read_to_delim = .ReadToDelim
call hotswap %1 .read_token = .ReadToken
call hotswap %1 .remove = .Remove
call hotswap %1 .remove_bytes = .RemoveBytes
call hotswap %1 .remove_pattern = .RemovePattern
call hotswap %1 .remove_pos = .RemovePos
call hotswap %1 .remove_prefix = .RemovePrefix
call hotswap %1 .remove_token = .RemoveToken
call hotswap %1 .replace = .Replace
call hotswap %1 .reverse = .Reverse
call hotswap %1 .rfind = .RFind
call hotswap %1 .rfind_any = .RfindAny
call hotswap %1 .seek_binary = .SeekBinary
call hotswap %1 .snip = .Snip
call hotswap %1 .split = .Split
call hotswap %1 .StreamString = .StreamZStr
call hotswap %1 .strip = .Strip
call hotswap %1 .subpos = .Subpos
call hotswap %1 .substr = .Substr
call hotswap %1 .tally = .Tally
call hotswap %1 .to_lower = .ToLower
call hotswap %1 .to_up_low = .ToUpLow
call hotswap %1 .to_upper = .ToUpper
call hotswap %1 .write_stream = .WriteStream
call hotswap %1 .write_string = .WriteString
call hotswap %1 .StdString = .ZStr
del *.old
goto done
:error
echo File name required.
:done