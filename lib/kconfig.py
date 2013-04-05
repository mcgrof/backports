#
# Small helper library to manipulate Kconfig files
#

import os, re

src_line = re.compile(r'^source\s+"?(?P<src>[^\s"]*)"?\s*$')
tri_line = re.compile(r'^(?P<spc>\s+)tristate')
cfg_line = re.compile(r'^(config|menuconfig)\s+(?P<sym>[^\s]*)')
sel_line = re.compile(r'^(?P<spc>\s+)select\s+(?P<sym>[^\s]*)\s*$')

class ConfigTree(object):
    def __init__(self, rootfile):
        self.basedir = os.path.dirname(rootfile)
        self.rootfile = os.path.basename(rootfile)

    def _walk(self, f):
        yield f
        for l in open(os.path.join(self.basedir, f), 'r'):
            m = src_line.match(l)
            if m and os.path.exists(os.path.join(self.basedir, m.group('src'))):
                for i in self._walk(m.group('src')):
                    yield i

    def _prune_sources(self, f, ignore):
        for nf in self._walk(f):
            out = ''
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = src_line.match(l)
                if not m:
                    out += l
                    continue
                src = m.group('src')
                if src in ignore or os.path.exists(os.path.join(self.basedir, src)):
                    out += l
                else:
                    out += '#' + l
            outf = open(os.path.join(self.basedir, nf), 'w')
            outf.write(out)
            outf.close()

    def prune_sources(self, ignore=[]):
        self._prune_sources(self.rootfile, ignore)

    def force_tristate_modular(self):
        for nf in self._walk(self.rootfile):
            out = ''
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = tri_line.match(l)
                out += l
                if m:
                    out += m.group('spc') + "depends on m\n"
            outf = open(os.path.join(self.basedir, nf), 'w')
            outf.write(out)
            outf.close()

    def symbols(self):
        syms = []
        for nf in self._walk(self.rootfile):
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = cfg_line.match(l)
                if m:
                    syms.append(m.group('sym'))
        return syms

    def modify_selects(self):
        syms = self.symbols()
        for nf in self._walk(self.rootfile):
            out = ''
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = sel_line.match(l)
                if m and not m.group('sym') in syms:
                    if 'BACKPORT_' + m.group('sym') in syms:
                        out += m.group('spc') + "select BACKPORT_" + m.group('sym') + '\n'
                    else:
                        out += m.group('spc') + "depends on " + m.group('sym') + '\n'
                else:
                    out += l
            outf = open(os.path.join(self.basedir, nf), 'w')
            outf.write(out)
            outf.close()

    def disable_symbols(self, syms):
        for nf in self._walk(self.rootfile):
            out = ''
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = cfg_line.match(l)
                out += l
                if m and m.group('sym') in syms:
                    out += "\tdepends on n\n"
            outf = open(os.path.join(self.basedir, nf), 'w')
            outf.write(out)
            outf.close()

    def add_dependencies(self, deps):
        for nf in self._walk(self.rootfile):
            out = ''
            for l in open(os.path.join(self.basedir, nf), 'r'):
                m = cfg_line.match(l)
                out += l
                if m:
                    for dep in deps.get(m.group('sym'), []):
                        out += "\tdepends on %s\n" % dep
            outf = open(os.path.join(self.basedir, nf), 'w')
            outf.write(out)
            outf.close()
