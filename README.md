<h1>Filesystem</h1>

<h2> TODO </h2>
<p>
Many operations do not work after restarting filesystem, no loading from disk to memory happens (e.g inode_table is empty). 
Change the inode names such that untokenized strings work with get_type.</p>
<p>Makefile</p>
<p> sfs_delete doesn't delete inode from disk </p>
<p> The following commands should now be working:
<ul>
  <li>o: open a file</li>
  <li>r: read from a file</li>
  <li>w: write to a file</li>
  <li>R: read from a directory</li>
  <li>c: close a file</li>
  <li>m: create (make) a new file</li>
  <li>s: get the size of a file</li>
  <li>t: get the type of a file</li>
  <li>i: initialize the file system option 1 (erase)</li>
  <li>q: quit - exit this program</li>
  </ul>
</p>
<p> The following need to be finished:
<ul>
  <li>d: delete a file</li>
  <li>i: initialize the file system option 0</li>
</ul>
</p>
