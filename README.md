<h1>Filesystem</h1>

<h2> TODO </h2>
<p>
Many operations do not work after restarting filesystem, no loading from disk to memory happens (e.g inode_table is empty). 
Change the inode names such that untokenized strings work with get_type.</p>
<p>Makefile</p>
<p> sfs_delete doesn't delete inode from disk </p>
<p> The following commands should now be working:

  o: open a file
  r: read from a file
  w: write to a file
  R: read from a directory
  c: close a file
  m: create (make) a new file
  s: get the size of a file
  t: get the type of a file
  i: initialize the file system option 1 (erase)
  q: quit - exit this program
</p>
<p> The following need to be finished:

  d: delete a file
  i: initialize the file system option 0
</p>
