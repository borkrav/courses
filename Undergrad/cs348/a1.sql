select professor.pnum, professor.pname, professor.dept \
from professor, schedule, class \
where professor.pnum = class.pnum \
and class.cnum = schedule.cnum \
and class.term=schedule.term \
and class.section = schedule.section \
and schedule.day = 'Friday' \
and schedule.time > '14:00' \
and exists (select * from mark \
where schedule.cnum = mark.cnum \
and schedule.term = mark.term \
and schedule.section = mark.section)

select distinct student.snum, student.sname \
from student, enrollment \
where student.snum = enrollment.snum \
and student.year = '4' \
and enrollment.cnum != 'CS348'

select distinct student.snum, mark.cnum, course.cname, mark.grade \
from student, class, course, professor, mark \
where student.sname = 'Smith, Fred' \
and student.snum = mark.snum \
and mark.cnum = class.cnum \
and mark.term = class.term \
and mark.section = class.section \
and class.pnum = professor.pnum \
and professor.dept != 'Computer Science' \
and course.cnum = class.cnum \
and substr(mark.cnum, 1,2) = 'CS'

select distinct student.snum, student.sname, student.year \
from student, mark \
where student.snum = mark.snum \
and student.year > '2' \
and 65 >= all \
(select grade \
from mark M2 \
where student.snum = M2.snum \
and substr(cnum, 1,2) = 'CS')

(select distinct professor.pnum, professor.pname, professor.office, professor.dept \
from professor, schedule, class \
where professor.pnum = class.pnum \
and class.cnum = schedule.cnum \
and class.term=schedule.term \
and class.section = schedule.section \
and not exists (select * from mark \
where schedule.cnum = mark.cnum \
and schedule.term = mark.term \
and schedule.section = mark.section)) \
except \
(select distinct professor.pnum, professor.pname, professor.office, professor.dept \
from professor, class, schedule a, schedule b \
where professor.pnum = class.pnum \
and class.cnum=a.cnum \
and class.cnum=b.cnum \
and class.term=a.term \
and class.term = b.term \
and class.section=a.section \
and class.section=b.section \
and (a.day = 'Monday' and a.time < '12:00' and b.day='Friday' and b.time > '12:00') \
and not exists (select * from mark \
where a.cnum = mark.cnum \
and a.term = mark.term \
and a.section = mark.section \
and b.cnum = mark.cnum \
and b.term = mark.term \
and b.section = mark.section)) \
order by dept,pname

select numofstudents*100/(select count(sname) as numofstudents \
from (select sname, avg(grade) as AVERAGE \
from (select student.sname, mark.grade \
from student, enrollment, mark \
where student.snum = enrollment.snum \
and enrollment.snum = mark.snum \
and enrollment.cnum = mark.cnum \
and enrollment.term = mark.term \
and enrollment.section = mark.section \
and student.year = '4' \
and substr (right(mark.cnum, 3),1,1) = '3') \
group by sname)) as percentage \
from (select count(sname) as numofstudents \
from (select sname, avg(grade) as AVERAGE \
from (select student.sname, mark.grade \
from student, enrollment, mark \
where student.snum = enrollment.snum \
and enrollment.snum = mark.snum \
and enrollment.cnum = mark.cnum \
and enrollment.term = mark.term \
and enrollment.section = mark.section \
and student.year = '4' \
and substr (right(mark.cnum, 3),1,1) = '3') \
group by sname) where average >=80)

select * from \
(select cnum, count(cnum) as enrollcount from enrollment group by cnum) \
where enrollcount in \
(select distinct enrollcount from \
(select cnum, count(cnum) as enrollcount from enrollment group by cnum order by enrollcount desc) \
fetch first 2 row only)

select pnum, pname, cnum, section, term, count(snum) as teaching \
from (select professor.pnum, professor.pname, enrollment.cnum, enrollment.section, enrollment.term, student.snum \
from professor, class, enrollment,student \
where student.year = '4' \
and professor.dept = 'Pure Math' \
and professor.pnum = class.pnum \
and class.cnum = enrollment.cnum \
and class.term = enrollment.term \
and class.section = enrollment.section \
and enrollment.snum = student.snum \
and not exists (select * from mark \
where enrollment.cnum = mark.cnum \
and enrollment.term = mark.term \
and enrollment.section = mark.section)) \
group by pnum, pname, cnum, section, term \
order by pname, pnum, cnum, term, section

select a.cnum, a.topgrade, b.cnum, b.topgrade \
from \
(select professor.pname, class.term, class.cnum, max(mark.grade) as topgrade \
from professor, class, enrollment, mark \
where professor.pnum = class.pnum \
and class.cnum = enrollment.cnum \
and class.section = enrollment.section \
and class.term = enrollment.term \
and enrollment.cnum = mark.cnum \
and enrollment.term = mark.term \
and enrollment.section = mark.section \
and professor.dept = 'Computer Science' \
group by professor.pname, class.term, class.cnum) a, \
(select professor.pname, class.term, class.cnum, max(mark.grade) as topgrade \
from professor, class, enrollment, mark \
where professor.pnum = class.pnum \
and class.cnum = enrollment.cnum \
and class.section = enrollment.section \
and class.term = enrollment.term \
and enrollment.cnum = mark.cnum \
and enrollment.term = mark.term \
and enrollment.section = mark.section \
and professor.dept = 'Computer Science' \
group by professor.pname, class.term, class.cnum) b \
where a.pname != b.pname \
and a.cnum = b.cnum

select count(dept)*100/(select count(distinct dept) from professor) \
from (select dept, count(pnum) as numberofprofs \
from (select * from professor \
where not exists \
(select a.pnum, a.pname, a.dept from \
(select distinct professor.pnum, professor.pname, professor.dept, class.cnum, class.term \
from professor, class \
where class.pnum = professor.pnum) a, \
(select distinct professor.pnum, professor.pname, professor.dept, class.cnum, class.term \
from professor, class \
where class.pnum = professor.pnum) b \
where a.pnum = b.pnum \
and a.pname = b.pname \
and a.dept = b.dept \
and a.cnum != b.cnum \
and a.term = b.term)) \
group by dept) \
where numberofprofs >= 2
