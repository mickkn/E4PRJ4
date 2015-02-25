echo off
FOR /r %%f IN (Master.pdf) do del %%f
FOR /r %%f IN (*.aux) do del %%f
FOR /r %%f IN (*.log) do del %%f
FOR /r %%f IN (*.out) do del %%f
FOR /r %%f IN (*.DS_Store) do del %%f
FOR /r %%f IN (*.gz) do del %%f
FOR /r %%f IN (*.toc) do del %%f
FOR /r %%r IN (Thumbs.db) do del %%f

echo on